// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_Lyzandred/Pickup/Coin/Lyz_CoinPickup.h"
#include "Project_Lyzandred/Pickup/Coin/Lyz_CoinType.h"
#include "Lyz_CoinMapper.generated.h"

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class PROJECT_LYZANDRED_API ULyz_CoinMapper : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category="Spawning")
	TArray<TSubclassOf<ALyz_CoinPickup>> GetCoinsToSpawn(const TArray<TSubclassOf<ULyz_CoinType>>& Coins);
	virtual TArray<TSubclassOf<ALyz_CoinPickup>> GetCoinsToSpawn_Implementation(const TArray<TSubclassOf<ULyz_CoinType>>& Coins);
};
