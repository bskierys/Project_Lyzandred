// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lyz_CoinSpawner.h"
#include "Lyz_CircleCoinSpawner.generated.h"

UCLASS(Blueprintable)
class PROJECT_LYZANDRED_API ALyz_CircleCoinSpawner : public ALyz_CoinSpawner
{
	GENERATED_BODY()

public:
	ALyz_CircleCoinSpawner();

protected:
	virtual void BeginPlay() override;
	
	virtual ALyz_CoinPickup* SpawnSingleCoin(const int32 Index, TSubclassOf<ALyz_CoinPickup> CoinClass) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Arrangement")
	float CoinSpawnRadius = 200.f;
};
