#include "QuestStage.h"

void UQuestStage::Init(UEventSubsystem* EventSystem)
{
	Super::Init(EventSystem);
}

void UQuestStage::Activate()
{
	if (InternalChangeState(EQuestState::Active))
	{
		ListenForCompletion();
	}
}

void UQuestStage::ListenForCompletion_Implementation()
{
}

void UQuestStage::CompleteStage()
{
	InternalChangeState(EQuestState::Completed);
}

bool UQuestStage::InternalChangeState(const EQuestState NewState)
{
	const EQuestState OldState = State;
	if (const bool SuperResult = Super::InternalChangeState(NewState); !SuperResult)
	{
		return false;
	}
	OnStageStateChanged.Broadcast(this, OldState, NewState);

	if (NewState == EQuestState::Completed)
	{
		// handle completed stage
		Clear();
	}
	return true;
}

void UQuestStage::Clear_Implementation()
{
	Super::Clear_Implementation();
	OnStageStateChanged.Clear();
}
