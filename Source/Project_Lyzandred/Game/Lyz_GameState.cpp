#include "Lyz_GameState.h"

void ALyz_GameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnKeyChanged.Clear();

	Super::EndPlay(EndPlayReason);
}

void ALyz_GameState::SetKey_Implementation(ULyz_KeyDefinition* Key, bool bValue)
{
	if (!IsValid(Key))
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Key modified: %s, value: %hhd"), *Key->KeyId.ToString(), bValue);
	
	KeyValues.Add(Key->KeyId, bValue);
	OnKeyChanged.Broadcast(Key->KeyId, bValue);
}

bool ALyz_GameState::GetKey(FName Id) const
{
	if (const bool* Found = KeyValues.Find(Id))
	{
		return *Found;
	}
	return false;
}

// TODO: Move form changing to form subsystem
void ALyz_GameState::SetCurrentCharacterForm(ULyz_KeyDefinition* NewForm, TArray<ULyz_KeyDefinition*> AvailableForms)
{
	if (!IsValid(NewForm))
	{
		return;
	}

	for (const auto Form: AvailableForms)
	{
		if (const auto KeyDefinition = Form; IsValid(KeyDefinition))
		{
			if (Form == NewForm)
			{
				CurrentCharacterForm = Form;
				SetKey(Form, true);
			}
			else
			{
				SetKey(Form, false);
			}
		}
	}
}
