#pragma once

#include "CoreMinimal.h"
#include "ETraversalDirection.h"
#include "GameFramework/Actor.h"
#include "Lyz_LevelLoader.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelLoaded, ALyz_LevelLoader*, Loader);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUnloaded, ALyz_LevelLoader*, Loader);

class ALyz_LevelLoadingManager;

UCLASS(Blueprintable)
class PROJECT_LYZANDRED_API ALyz_LevelLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	ALyz_LevelLoader();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category="Events")
	void NotifyLevelUnLoaded();

	UFUNCTION(BlueprintCallable, Category="Events")
	void NotifyLevelLoaded();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static ETraversalDirection ComputeCrossDirection(float EntryDot, float ExitDot);

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Level")
	TSoftObjectPtr<UWorld> LevelToLoad = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Level")
	ALyz_LevelLoadingManager* AssignedManager = nullptr;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Events")
	void LoadLevel();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Events")
	void UnLoadLevel();

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnLevelLoaded OnLevelLoaded;

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnLevelLoaded OnLevelUnLoaded;

	
};
