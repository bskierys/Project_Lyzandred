#include "Lyz_GameStateLibrary.h"
#include "Project_Lyzandred/Lyz_WorldLibrary.h"
#include "Project_Lyzandred/Character/Form/FormDataAsset.h"

ALyz_GameState* ULyz_GameStateLibrary::GetLyzGameState()
{
	const UWorld* World = ULyz_WorldLibrary::GetWorldSafe();

	if (!IsValid(World))
	{
		return nullptr;
	}

	auto* GS = World->GetGameState();

	if (!IsValid(GS) || !GS->IsA(ALyz_GameState::StaticClass()))
	{
		return nullptr;
	}
	
	return Cast<ALyz_GameState>(GS);
}

bool ULyz_GameStateLibrary::IsCharacterInForm(const UFormDataAsset* FormData, const TMap<FName, bool> KeyValues)
{
	const ULyz_KeyDefinition* Key = FormData->KeyDefinition;
	if (!IsValid(Key))
	{
		return false;
	}
	const FName KeyId = Key->KeyId;

	return KeyValues.Contains(KeyId) && KeyValues[KeyId];
}
