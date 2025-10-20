#include "Lyz_LevelLoadingManager.h"
#include "Lyz_LevelLoader.h"

ALyz_LevelLoadingManager::ALyz_LevelLoadingManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALyz_LevelLoadingManager::BeginPlay()
{
	Super::BeginPlay();
}

void ALyz_LevelLoadingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALyz_LevelLoadingManager::RegisterLevelLoader(ALyz_LevelLoader* LevelLoader)
{
	if (!IsValid(LevelLoader))
	{
		return;
	}

	LevelLoadersOnLevel.Add(LevelLoader);
}

void ALyz_LevelLoadingManager::UnregisterLevelLoader(ALyz_LevelLoader* LevelLoader)
{
	if (!IsValid(LevelLoader))
	{
		return;
	}

	if (!LevelLoadersOnLevel.Contains(LevelLoader))
	{
		return;
	}

	LevelLoadersOnLevel.Remove(LevelLoader);
}

