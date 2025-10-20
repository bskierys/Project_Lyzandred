#pragma once

#include "CoreMinimal.h"
#include "ETraversalDirection.h"
#include "GameFramework/Actor.h"
#include "Lyz_LevelLoader.generated.h"

class ULevelLoaderSubsystem;
class ULevelDataAsset;

UCLASS(Blueprintable)
class PROJECT_LYZANDRED_API ALyz_LevelLoader : public AActor
{
	GENERATED_BODY()

public:
	ALyz_LevelLoader();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static ETraversalDirection ComputeCrossDirection(float EntryDot, float ExitDot);

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Level")
	ULevelDataAsset* LevelToLoad = nullptr;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Events")
	void LoadLevel();
	virtual void LoadLevel_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Events")
	void UnloadLevel();
	virtual void UnloadLevel_Implementation();

protected:
	UPROPERTY()
	ULevelLoaderSubsystem* LevelLoaderSubsystem = nullptr;
};
