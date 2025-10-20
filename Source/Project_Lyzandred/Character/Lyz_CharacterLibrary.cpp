#include "Lyz_CharacterLibrary.h"

#include "Lyz_TriformCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Project_Lyzandred/Lyz_WorldLibrary.h"

bool ULyz_CharacterLibrary::CheckIfCurrentPlayerPawn(AActor* Actor)
{
	if (!IsValid(Actor))
	{
		return false;
	}

    const UWorld* World = ULyz_WorldLibrary::GetWorldSafe();

	if (!IsValid(World))
	{
		return false;
	}

	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(World, 0);
	
	if (!IsValid(PlayerPawn))
	{
		return false;
	}

	if (PlayerPawn != Actor)
	{
		return false;
	}

	return true;
}

ALyz_TriformCharacter* ULyz_CharacterLibrary::GetPlayerPawnAsTriformCharacter()
{
	const UWorld* World = ULyz_WorldLibrary::GetWorldSafe();

	if (!IsValid(World))
	{
		return nullptr;
	}
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(World, 0);
	
	if (!IsValid(PlayerPawn)  || !PlayerPawn->IsA(ALyz_TriformCharacter::StaticClass()))
	{
		return nullptr;
	}
	
	return Cast<ALyz_TriformCharacter>(PlayerPawn);
}
