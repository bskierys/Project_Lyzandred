#include "QuestSubsystem.h"
#include "Quest.h"
#include "QuestSubsystemConfig.h"
#include "Events/QuestStageStateChangePayload.h"
#include "Events/QuestStateChangePayload.h"
#include "Events/TrackedQuestChangedPayload.h"
#include "Project_Lyzandred/Events/EventChannelObject.h"
#include "Project_Lyzandred/Events/EventSubsystem.h"
#include "Project_Lyzandred/Other/Lyz_DeveloperSettings.h"

DEFINE_LOG_CATEGORY(LyzQuestSystem)

void UQuestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	const ULyz_DeveloperSettings* Settings = GetDefault<ULyz_DeveloperSettings>();
	if (!Settings)
	{
		UE_LOG(LyzQuestSystem, Error, TEXT("ULyz_DeveloperSettings is empty"));
		return;
	}

	auto* Subsystem = GetGameInstance()->GetSubsystem<UEventSubsystem>();
	Config = Cast<UQuestSubsystemConfig>(Settings->GetSubsystemConfigByClass(UQuestSubsystemConfig::StaticClass()));
	if (Config)
	{
		TArray<FName> InactiveQuests;

		for (const auto& Quest : Config->Quests)
		{
			// clear everything before initializing to be sure
			Quest->ResetAndClear();
			Quest->Init(Subsystem);
			Quest->OnQuestStateChanged.AddDynamic(this, &UQuestSubsystem::OnQuestStateChanged);
			Quest->OnQuestStageStateChanged.AddDynamic(this, &UQuestSubsystem::OnQuestStageStateChanged);
			QuestMap.Add(Quest->Id, Quest);
			InactiveQuests.Add(Quest->Id);
		}
		QuestStates.Add(EQuestState::Inactive, InactiveQuests);
		QuestEventChannel = Subsystem->GetEventChannel(Config->QuestEventChannel);

		UE_LOG(LyzQuestSystem, Log, TEXT("UQuestSubsystemConfig config set correct"));
	}
	else
	{
		UE_LOG(LyzQuestSystem, Error, TEXT("UQuestSubsystemConfig config set incorrect"));
	}

	UE_LOG(LyzQuestSystem, Log, TEXT("QuestSubsystem initialized"));
}

void UQuestSubsystem::Deinitialize()
{
	// clear all the quest listeners just to be sure
	for (const auto& Quest : QuestMap)
	{
		Quest.Value->Clear();
	}
	UE_LOG(LyzQuestSystem, Log, TEXT("QuestSubsystem deinitialized"));
	Super::Deinitialize();
}

TArray<UQuest*> UQuestSubsystem::GetQuestsWithState(const EQuestState QuestState)
{
	TArray<UQuest*> Result;
	if (!IsValid(Config))
	{
		UE_LOG(LyzQuestSystem, Error, TEXT("UQuestSubsystemConfig config is incorrect"));
		return Result;
	}
	if (QuestStates.Contains(QuestState))
	{
		const auto& QuestOfState = QuestStates.Find(QuestState);
		for (const auto& QuestId : *QuestOfState)
		{
			if (const auto Found = QuestMap.Find(QuestId))
			{
				Result.Add(*Found);
			}
		}
	}

	return Result;
}

UQuest* UQuestSubsystem::GetQuestForId(const FName QuestId)
{
	if (!IsValid(Config))
	{
		UE_LOG(LyzQuestSystem, Error, TEXT("UQuestSubsystemConfig config is incorrect"));
		return nullptr;
	}
	if (const auto Found = QuestMap.Find(QuestId))
	{
		return *Found;
	}
	return nullptr;
}

void UQuestSubsystem::OnQuestStateChanged(UQuest* Quest, const EQuestState OldState, const EQuestState NewState)
{
	if (!IsValid(Config))
	{
		UE_LOG(LyzQuestSystem, Error, TEXT("UQuestSubsystemConfig config is incorrect"));
		return;
	}

	if (OldState == EQuestState::Completed && NewState == EQuestState::Active)
	{
		UE_LOG(LyzQuestSystem, Warning,
		       TEXT("Received an event to change the quest %s state from Completed to Active. Aborting."),
		       *Quest->Id.ToString()
		);
		return;
	}

	if (OldState == NewState)
	{
		UE_LOG(LyzQuestSystem, Log,
		       TEXT("Received an event to change the quest %s state but already of that state. Aborting."),
		       *Quest->Id.ToString()
		);
		return;
	}

	if (QuestStates.Contains(OldState) && QuestStates[OldState].Contains(Quest->Id))
	{
		QuestStates[OldState].Remove(Quest->Id);
	}
	else
	{
		UE_LOG(LyzQuestSystem, Warning,
		       TEXT("Requested to change the quest state but could"
			       "not find the Quest in subsystem state. Aborting.")
		);
		return;
	}

	switch (NewState)
	{
	case EQuestState::Active:
		HandleQuestActivated(Quest);
		break;
	case EQuestState::Completed:
		HandleQuestCompleted(Quest);
		break;
	case EQuestState::Inactive:
	default:
		break;
	}

	if (QuestStates.Contains(NewState))
	{
		QuestStates[NewState].Add(Quest->Id);
	}
	else
	{
		TArray<FName> NewQuests;
		NewQuests.Add(Quest->Id);
		QuestStates.Add(NewState, NewQuests);
	}

	if (IsValid(QuestEventChannel))
	{
		UQuestStateChangePayload* Payload = NewObject<UQuestStateChangePayload>();
		Payload->Quest = Quest;
		Payload->OldState = OldState;
		Payload->NewState = NewState;
		QuestEventChannel->Broadcast(NAME_EventQuestChanged, this, Payload);
	}
}

void UQuestSubsystem::HandleQuestActivated(UQuest* Quest)
{
	if (!TrackedQuest)
	{
		StartTrackingQuest(Quest);
	}
}

void UQuestSubsystem::HandleQuestCompleted(const UQuest* Quest)
{
	if (TrackedQuest == Quest)
	{
		// Tracked quest completed. We need to find the next one.
		const auto& ActiveQuests = QuestStates.FindRef(EQuestState::Active);
		if (!ActiveQuests.IsEmpty())
		{
			const auto NewQuest = QuestMap.FindRef(ActiveQuests[0]);
			StartTrackingQuest(NewQuest);
		}
		else
		{
			// No Quest to track
			StartTrackingQuest(nullptr);
		}
	}
}

void UQuestSubsystem::StartTrackingQuest(UQuest* Quest)
{
	UQuest* OldQuest = TrackedQuest;
	TrackedQuest = Quest;

	if (IsValid(QuestEventChannel))
	{
		UTrackedQuestChangedPayload* Payload = NewObject<UTrackedQuestChangedPayload>();
		Payload->OldQuest = OldQuest;
		Payload->NewQuest = Quest;
		QuestEventChannel->Broadcast(NAME_TrackedQuestChange, this, Payload);
	}

	if (IsValid(Quest))
	{
		UE_LOG(LyzQuestSystem, Log, TEXT("Quest %s is now being tracked"), *Quest->Id.ToString());
	}
	else
	{
		UE_LOG(LyzQuestSystem, Log, TEXT("Cleared Tracked Quest"));
	}
}

void UQuestSubsystem::OnQuestStageStateChanged(
	UQuest* Quest, UQuestStage* QuestStage, const int32 StageIndex,
	const EQuestState OldState, const EQuestState NewState
)
{
	if (OldState == EQuestState::Completed && NewState == EQuestState::Active)
	{
		UE_LOG(LyzQuestSystem, Warning,
		       TEXT("Received an event of change of the stage %s state from Completed to Active. Aborting."),
		       *QuestStage->Id.ToString()
		);
		return;
	}

	if (IsValid(QuestEventChannel))
	{
		UQuestStageStateChangePayload* Payload = NewObject<UQuestStageStateChangePayload>();
		Payload->Quest = Quest;
		Payload->QuestStage = QuestStage;
		Payload->StageIndex = StageIndex;
		Payload->OldState = OldState;
		Payload->NewState = NewState;
		QuestEventChannel->Broadcast(NAME_EventQuestStageChanged, this, Payload);
	}
}
