#include "QuestBase.h"
#include "QuestSubsystem.h"

void UQuestBase::Init(UEventSubsystem* EventSystem)
{
	EventSubsystem = EventSystem;
	State = EQuestState::Inactive;
}

void UQuestBase::ResetAndClear()
{
	State = EQuestState::Inactive;
	Clear();
}

void UQuestBase::Clear_Implementation()
{
}

bool UQuestBase::InternalChangeState(const EQuestState NewState)
{
	const EQuestState OldState = State;
	const FString OldStateStr = UEnum::GetValueAsString(OldState);
	const FString NewStateStr = UEnum::GetValueAsString(NewState);
	if (State == NewState)
	{
		UE_LOG(LyzQuestSystem, Log,
			TEXT("Quest object: %s state is already %s. Change aborted."),
			*Id.ToString(),
			*NewStateStr
		);
		return false;
	}
	if (State == EQuestState::Completed)
	{
		UE_LOG(LyzQuestSystem, Warning,
			TEXT("Internal State Change: Can't update Completed Quest Object %s"),
			*Id.ToString()
		);
		return false;
	}
	
	State = NewState;
	UE_LOG(LyzQuestSystem, Log,
		TEXT("Quest Object: %s state changed from %s to %s"),
		*Id.ToString(),
		*OldStateStr,
		*NewStateStr
	);
	
	return true;
}
