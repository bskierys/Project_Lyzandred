#include "Lyz_Key.h"

#include "Kismet/GameplayStatics.h"
#include "Project_Lyzandred/Character/Lyz_CharacterLibrary.h"
#include "Project_Lyzandred/Game/Lyz_GameStateLibrary.h"

ALyz_Key::ALyz_Key()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALyz_Key::BeginPlay()
{
	Super::BeginPlay();
	
	GameStateRef = ULyz_GameStateLibrary::GetLyzGameState();
}

void ALyz_Key::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALyz_Key::CollectKey(AActor* OtherActor)
{
	if (!ULyz_CharacterLibrary::CheckIfCurrentPlayerPawn(OtherActor))
	{
		return;
	}
	
	if (!IsValid(GameStateRef))
	{
		return;
	}

	if (!IsValid(KeyDefinition))
	{
		return;
	}

	if (CollectSound)
	{
		const FVector Location = GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(this, CollectSound, Location);
	}
	
	GameStateRef->SetKey(KeyDefinition, true);

	Destroy();
}
