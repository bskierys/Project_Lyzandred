#include "Lyz_LevelLoader.h"
#include "Lyz_LevelLoadingManager.h"

ALyz_LevelLoader::ALyz_LevelLoader()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALyz_LevelLoader::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AssignedManager))
	{
		AssignedManager->RegisterLevelLoader(this);
	}
}

void ALyz_LevelLoader::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnLevelLoaded.Clear();
	OnLevelUnLoaded.Clear();

	if (IsValid(AssignedManager))
	{
		AssignedManager->UnregisterLevelLoader(this);
	}

	Super::EndPlay(EndPlayReason);
}

void ALyz_LevelLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALyz_LevelLoader::NotifyLevelLoaded()
{
	OnLevelLoaded.Broadcast(this);
}

ETraversalDirection ALyz_LevelLoader::ComputeCrossDirection(float EntryDot, float ExitDot)
{
	if (EntryDot < 0 && ExitDot > 0)
	{
		return ETraversalDirection::Forward;
	}

	if (EntryDot > 0 && ExitDot < 0)
	{
		return ETraversalDirection::Backward;
	}

	return ETraversalDirection::Returned;
}

void ALyz_LevelLoader::NotifyLevelUnLoaded()
{
	OnLevelUnLoaded.Broadcast(this);
}

