// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lyz_LevelLoader.h"
#include "GameFramework/Actor.h"
#include "Lyz_LevelLoadingManager.generated.h"

class ALyz_LevelLoader;

UCLASS()
class PROJECT_LYZANDRED_API ALyz_LevelLoadingManager : public AActor
{
	GENERATED_BODY()
	
public:
	ALyz_LevelLoadingManager();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Loaders")
	TArray<ALyz_LevelLoader const *> LevelLoadersOnLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Loaders")
	ALyz_LevelLoader* ActiveLoader = nullptr;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Loaders")
	void RegisterLevelLoader(ALyz_LevelLoader* LevelLoader);

	UFUNCTION(BlueprintCallable, Category="Loaders")
	void UnregisterLevelLoader(ALyz_LevelLoader* LevelLoader);
};
