#include "Quest.h"
#include "QuestStage.h"
#include "QuestSubsystem.h"

void UQuest::Init(UEventSubsystem* EventSystem)
{
	Super::Init(EventSystem);
	CurrentStageIndex = -1;
	for (const auto& Stage : Stages)
	{
		Stage->Init(EventSystem);
		Stage->ResetAndClear();
		StagesStatesMap.Add(Stage->Id, EQuestState::Inactive);
		Stage->OnStageStateChanged.AddDynamic(this, &UQuest::OnStageStateChanged);
	}
	ListenForActivation();
}

void UQuest::ListenForActivation_Implementation()
{
}

void UQuest::ActivateQuest()
{
	if (InternalChangeState(EQuestState::Active))
	{
		CurrentStageIndex = -1;
		AdvanceToNextStage();
	}
}

void UQuest::ResetAndClear()
{
	State = EQuestState::Inactive;
	for (const auto& Stage : Stages)
	{
		Stage->ResetAndClear();
		StagesStatesMap.Add(Stage->Id, EQuestState::Inactive);
	}
	Clear();
}

UQuestStage* UQuest::GetCurrentStage() const
{
	if (State == EQuestState::Inactive || CurrentStageIndex < 0 || CurrentStageIndex >= Stages.Num())
	{
		return nullptr;
	}

	return Stages[CurrentStageIndex];
}

void UQuest::Clear_Implementation()
{
	OnQuestStateChanged.Clear();
	OnQuestStageStateChanged.Clear();
	for (const auto& Stage : Stages)
	{
		Stage->Clear();
	}
}

bool UQuest::InternalChangeState(EQuestState NewState)
{
	const EQuestState OldState = State;
	if (const bool SuperResult = Super::InternalChangeState(NewState); !SuperResult)
	{
		return false;
	}
	OnQuestStateChanged.Broadcast(this, OldState, NewState);

	if (NewState == EQuestState::Completed)
	{
		// handle completed quest
		Clear();
	}
	return true;
}

void UQuest::AdvanceToNextStage()
{
	const int32 NewStageIndex = CurrentStageIndex + 1;
	if (NewStageIndex >= Stages.Num())
	{
		UE_LOG(LyzQuestSystem, Warning, TEXT("Can't Advance to next stage. This was the last one."));
		return;
	}

	CurrentStageIndex = NewStageIndex;
	UQuestStage* NextStage = Stages[CurrentStageIndex];
	NextStage->Activate();

	OnNewStage.Broadcast(this, NextStage);
	
	UE_LOG(LyzQuestSystem, Log,
	       TEXT("Quest: %s Advanced to next Stage: %s, %d/%d"),
	       *Id.ToString(),
	       *NextStage->Id.ToString(),
	       CurrentStageIndex + 1,
	       Stages.Num()
	);
}

void UQuest::OnStageStateChanged(UQuestStage* QuestStage, EQuestState OldState, EQuestState NewState)
{
	if (State == EQuestState::Completed || State == EQuestState::Inactive)
	{
		UE_LOG(LyzQuestSystem, Warning, TEXT("Stage State Change: Can't update Completed or Inactive Quest"));
		return;
	}

	if (!StagesStatesMap.Contains(QuestStage->Id))
	{
		UE_LOG(LyzQuestSystem, Error, TEXT("Unknown Stage state changed in the quest"));
		return;
	}

	const int32 Index = Stages.IndexOfByKey(QuestStage);

	// propagate up
	OnQuestStageStateChanged.Broadcast(this, QuestStage, Index, OldState, NewState);
	// change internal state
	StagesStatesMap[QuestStage->Id] = NewState;

	if (NewState == EQuestState::Completed)
	{
		bool bIsQuestCompleted = true;
		for (const auto& StageState : StagesStatesMap)
		{
			if (StageState.Value != EQuestState::Completed)
			{
				bIsQuestCompleted = false;
				break;
			}
		}

		if (bIsQuestCompleted)
		{
			InternalChangeState(EQuestState::Completed);
		}
		else
		{
			const int32 NewStageIndex = CurrentStageIndex + 1;
			if (NewStageIndex >= Stages.Num())
			{
				UE_LOG(LyzQuestSystem, Error, TEXT("Invalid Quest state. Stage Advanced beyond array boundaries."));
				return;
			}
			AdvanceToNextStage();
		}
	}
}
