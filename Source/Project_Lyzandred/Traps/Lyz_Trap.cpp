#include "Lyz_Trap.h"
#include "Project_Lyzandred/Character/Lyz_TriformCharacter.h"

ALyz_Trap::ALyz_Trap()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALyz_Trap::BeginPlay()
{
	Super::BeginPlay();
}

void ALyz_Trap::KillPawn(AActor* OtherActor)
{
	if (IsValid(OtherActor) && OtherActor->GetClass()->ImplementsInterface(ULyz_KillableInterface::StaticClass()))
	{
		ILyz_KillableInterface::Execute_Kill(OtherActor);
	}
}

void ALyz_Trap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
