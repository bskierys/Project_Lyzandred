#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LevelLoaderSubsystem.generated.h"

class ULevelDataAsset;

DECLARE_LOG_CATEGORY_EXTERN(LyzLevelLoader, Log, All);

UENUM()
enum class ESublevelState : uint8
{
	Unloaded = 0,
	Loading = 1,
	Loaded = 2,
	Unloading = 3
};

struct FSublevelInfo
{
	FName SublevelName;
	ESublevelState State = ESublevelState::Unloaded;
};

USTRUCT()
struct FRegisteredLevel
{
	GENERATED_BODY()
	
	FName LevelName;
	
	UPROPERTY()
	const ULevelDataAsset* Data = nullptr;
	
	TMap<FName, FSublevelInfo> Sublevels;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAllSublevelsLoaded, FName, LevelName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAllSublevelsUnloaded, FName, LevelName);

UCLASS(BlueprintType, Blueprintable)
class PROJECT_LYZANDRED_API ULevelLoaderSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	/**
	 * Load all sublevels from data asset
	 * @param LevelData
	 * @param bUnloadOtherLevels Whether to unload all other levels
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void LoadSublevelsFromData(const ULevelDataAsset* LevelData, bool bUnloadOtherLevels);

	/**
	 * Unload all sublevels from data asset
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void UnloadSublevelsFromData(const ULevelDataAsset* LevelData);

	/**
	 * Register a level so the subsystem knows about it
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void RegisterLevel(const ULevelDataAsset* LevelData);

	UPROPERTY(BlueprintAssignable)
	FOnAllSublevelsLoaded OnAllSublevelsLoaded;

	UPROPERTY(BlueprintAssignable)
	FOnAllSublevelsUnloaded OnAllSublevelsUnloaded;

protected:
	void OnLevelAdded(ULevel* LoadedLevel, UWorld* OwningWorld);
	void OnLevelRemoved(ULevel* UnloadedLevel, UWorld* OwningWorld);

	void NotifyAllSublevelsLoaded(FName LevelName) const;
	void NotifyAllSublevelsUnloaded(FName LevelName) const;

private:
	UPROPERTY()
	TMap<FName, FRegisteredLevel> RegisteredLevels;
	
	FName ActiveLevelName;
};
