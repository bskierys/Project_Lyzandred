#include "LevelLoaderSubsystem.h"

#include "LevelDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Project_Lyzandred/Lyz_WorldLibrary.h"

DEFINE_LOG_CATEGORY(LyzLevelLoader)

void ULevelLoaderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FWorldDelegates::LevelAddedToWorld.AddUObject(this, &ULevelLoaderSubsystem::OnLevelAdded);
	FWorldDelegates::LevelRemovedFromWorld.AddUObject(this, &ULevelLoaderSubsystem::OnLevelRemoved);

	UE_LOG(LyzLevelLoader, Log, TEXT("LevelLoaderSubsystem initialized"));
}

void ULevelLoaderSubsystem::Deinitialize()
{
	FWorldDelegates::LevelAddedToWorld.RemoveAll(this);
	FWorldDelegates::LevelRemovedFromWorld.RemoveAll(this);
	RegisteredLevels.Empty();
	
	UE_LOG(LyzLevelLoader, Log, TEXT("LevelLoaderSubsystem deinitialized"));
	Super::Deinitialize();
}

void ULevelLoaderSubsystem::RegisterLevel(const ULevelDataAsset* LevelData)
{
	if (!LevelData)
	{
		return;
	}

	const FName LevelName = LevelData->LevelName;
	FRegisteredLevel& Level = RegisteredLevels.FindOrAdd(LevelName);
	Level.LevelName = LevelName;
	Level.Data = LevelData;

	for (const TSoftObjectPtr<UWorld>& SublevelPtr : LevelData->Sublevels)
	{
		FSoftObjectPath Path = SublevelPtr.ToSoftObjectPath();
		if (!Path.IsValid())
		{
			continue;
		}

		FName SubName(*Path.GetAssetName());
		FSublevelInfo& Info = Level.Sublevels.FindOrAdd(SubName);
		Info.SublevelName = SubName;
		Info.State = ESublevelState::Unloaded;
	}
	UE_LOG(
		LyzLevelLoader, Log,
		TEXT("Registered level %s with %d sublevels."),
		*LevelName.ToString(), Level.Sublevels.Num()
	);
}

void ULevelLoaderSubsystem::LoadSublevelsFromData(const ULevelDataAsset* LevelData, bool bUnloadOtherLevels)
{
	if (!IsValid(LevelData))
	{
		return;
	}

	const UWorld* World = ULyz_WorldLibrary::GetWorldSafe();
	if (!World)
	{
		return;
	}

	const FName LevelName = LevelData->LevelName;
	if (!RegisteredLevels.Contains(LevelName))
	{
		UE_LOG(LyzLevelLoader, Warning, TEXT("Trying to load unregistered level: %s"), *LevelName.ToString());
		return;
	}

	// unload levels if requested
	if (bUnloadOtherLevels)
	{
		for (auto& Pair : RegisteredLevels)
		{
			if (Pair.Key != LevelName)
			{
				UnloadSublevelsFromData(Pair.Value.Data);
			}
		}
	}

	// load level
	FRegisteredLevel& Level = RegisteredLevels[LevelName];
	for (auto& Pair: Level.Sublevels)
	{
		FSublevelInfo& Info = Pair.Value;

		switch (Info.State)
		{
		case ESublevelState::Unloaded:
			Info.State = ESublevelState::Loading;
			UE_LOG(LyzLevelLoader, Log, TEXT("Loading sublevel: %s"), *Info.SublevelName.ToString());
			UGameplayStatics::LoadStreamLevel(World, Info.SublevelName, true, false, FLatentActionInfo());
			break;

		case ESublevelState::Unloading:
			Info.State = ESublevelState::Loading;
			// This needs to be tested better as I have only single sublevels on the test map
			UE_LOG(LyzLevelLoader, Log, TEXT("Sublevel %s was unloading, switching to loading"), *Info.SublevelName.ToString());
			UGameplayStatics::LoadStreamLevel(World, Info.SublevelName, true, false, FLatentActionInfo());
			break;

		case ESublevelState::Loading:
		case ESublevelState::Loaded:
			UE_LOG(LyzLevelLoader, Verbose, TEXT("Sublevel %s already loaded"), *Info.SublevelName.ToString());
			break;
		}
	}

	ActiveLevelName = LevelName;
}

void ULevelLoaderSubsystem::UnloadSublevelsFromData(const ULevelDataAsset* LevelData)
{
	if (!IsValid(LevelData))
	{
		return;
	}

	const UWorld* World = ULyz_WorldLibrary::GetWorldSafe();
	if (!World)
	{
		return;
	}

	const FName LevelName = LevelData->LevelName;
	if (!RegisteredLevels.Contains(LevelName))
	{
		UE_LOG(LyzLevelLoader, Warning, TEXT("Trying to unload unregistered level: %s"), *LevelName.ToString());
		return;
	}

	FRegisteredLevel& Level = RegisteredLevels[LevelName];
	for (auto& Pair: Level.Sublevels)
	{
		FSublevelInfo& Info = Pair.Value;

		switch (Info.State)
		{
		case ESublevelState::Loaded:
			Info.State = ESublevelState::Unloading;
			UE_LOG(LyzLevelLoader, Log, TEXT("Unloading sublevel: %s"), *Info.SublevelName.ToString());
			UGameplayStatics::UnloadStreamLevel(World, Info.SublevelName, FLatentActionInfo(), false);
			break;

		case ESublevelState::Loading:
			Info.State = ESublevelState::Unloading;
			UE_LOG(LyzLevelLoader, Log, TEXT("Sublevel %s was loading, switching to unloading"), *Info.SublevelName.ToString());
			UGameplayStatics::UnloadStreamLevel(World, Info.SublevelName, FLatentActionInfo(), false);
			break;

		case ESublevelState::Unloaded:
		case ESublevelState::Unloading:
			UE_LOG(LyzLevelLoader, Verbose, TEXT("Sublevel %s already unloaded"), *Info.SublevelName.ToString());
			break;
		}
	}

	if (ActiveLevelName == LevelName)
	{
		ActiveLevelName = NAME_None;
	}
}

void ULevelLoaderSubsystem::OnLevelAdded(ULevel* LoadedLevel, UWorld* OwningWorld)
{
	if (!LoadedLevel)
	{
		return;
	}

	const FName SubName = LoadedLevel->GetOuter()->GetFName();

	for (auto& Pair : RegisteredLevels)
	{
		if (FSublevelInfo* Info = Pair.Value.Sublevels.Find(SubName))
		{
			Info->State = ESublevelState::Loaded;
			UE_LOG(LyzLevelLoader, Log, TEXT("Sublevel loaded: %s"), *SubName.ToString());

			bool bAllLoaded = true;
			for (const auto& SubPair : Pair.Value.Sublevels)
			{
				if (SubPair.Value.State != ESublevelState::Loaded)
				{
					bAllLoaded = false;
					break;
				}
			}
			if (!Pair.Value.Sublevels.IsEmpty() && bAllLoaded)
			{
				NotifyAllSublevelsLoaded(Pair.Key);
			}
			break;
		}
	}
}

void ULevelLoaderSubsystem::OnLevelRemoved(ULevel* UnloadedLevel, UWorld* OwningWorld)
{
	if (!UnloadedLevel)
	{
		return;
	}

	const FName SubName = UnloadedLevel->GetOuter()->GetFName();

	for (auto& Pair : RegisteredLevels)
	{
		if (FSublevelInfo* Info = Pair.Value.Sublevels.Find(SubName))
		{
			Info->State = ESublevelState::Unloaded;
			UE_LOG(LyzLevelLoader, Log, TEXT("Sublevel unloaded: %s"), *SubName.ToString());

			bool bAllUnloaded = true;
			for (const auto& SubPair : Pair.Value.Sublevels)
			{
				if (SubPair.Value.State != ESublevelState::Unloaded)
				{
					bAllUnloaded = false;
					break;
				}
			}
			if (!Pair.Value.Sublevels.IsEmpty() && bAllUnloaded)
			{
				NotifyAllSublevelsUnloaded(Pair.Key);
			}
			break;
		}
	}
}

void ULevelLoaderSubsystem::NotifyAllSublevelsLoaded(FName LevelName) const
{
	UE_LOG(LyzLevelLoader, Log, TEXT("All sublevels finished loading"));
	OnAllSublevelsLoaded.Broadcast(LevelName);
}

void ULevelLoaderSubsystem::NotifyAllSublevelsUnloaded(FName LevelName) const
{
	UE_LOG(LyzLevelLoader, Log, TEXT("All sublevels finished unloading"));
	OnAllSublevelsUnloaded.Broadcast(LevelName);
}
