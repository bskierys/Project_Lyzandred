#include "Lyz_LevelLoader.h"
#include "LevelDataAsset.h"
#include "LevelLoaderSubsystem.h"
#include "Project_Lyzandred/Lyz_WorldLibrary.h"

ALyz_LevelLoader::ALyz_LevelLoader()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALyz_LevelLoader::BeginPlay()
{
	Super::BeginPlay();

	const UWorld* World = ULyz_WorldLibrary::GetWorldSafe();
	if (World)
	{
		LevelLoaderSubsystem = World->GetSubsystem<ULevelLoaderSubsystem>();
	}

	if (!LevelLoaderSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("LevelLoadingSubsystem not found"));
		return;
	}

	if (LevelToLoad)
	{
		LevelLoaderSubsystem->RegisterLevel(LevelToLoad);
	}
}

void ALyz_LevelLoader::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ALyz_LevelLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALyz_LevelLoader::LoadLevel_Implementation()
{
	if (!LevelLoaderSubsystem || !LevelToLoad)
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing subsystem or LevelData"));
		return;
	}

	LevelLoaderSubsystem->LoadSublevelsFromData(LevelToLoad, true);
}

void ALyz_LevelLoader::UnloadLevel_Implementation()
{
	if (!LevelLoaderSubsystem || !LevelToLoad)
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing subsystem or LevelData"));
		return;
	}

	LevelLoaderSubsystem->UnloadSublevelsFromData(LevelToLoad);
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
