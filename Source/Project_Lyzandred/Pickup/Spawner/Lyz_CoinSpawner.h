// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Project_Lyzandred/Pickup/Coin/Lyz_CoinType.h"
#include "Project_Lyzandred/Pickup/Coin/Lyz_CoinPickup.h"
#include "Project_Lyzandred/Pickup/Mapper/Lyz_CoinMapper.h"
#include "Lyz_CoinSpawner.generated.h"

class ALyz_CoinPickup;

UCLASS(Abstract)
class PROJECT_LYZANDRED_API ALyz_CoinSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ALyz_CoinSpawner();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	// Params
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Coins")
	TMap<TSubclassOf<ULyz_CoinType>, int32> Coins;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Visibility")
	bool bCoinsVisible = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Visibility")
	float DelayBetweenShowingCoins = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Strategy", meta=(BlueprintBaseOnly="true"))
	ULyz_CoinMapper* CoinMapper = nullptr;

	// Functions
	UFUNCTION(BlueprintCallable)
	void AnimateCoinSpawn();

protected:
	UPROPERTY()
	TArray<ALyz_CoinPickup*> SpawnedCoins;

	UPROPERTY()
	TArray<TSubclassOf<ULyz_CoinType>> CoinTypesToSpawn;

	// pure virtual/ has to be implemented in the child classes
	virtual ALyz_CoinPickup* SpawnSingleCoin(const int32 Index, TSubclassOf<ALyz_CoinPickup> CoinClass)
	PURE_VIRTUAL(ALyz_CoinPickup::SpawnSingleCoin, return nullptr;);

	ALyz_CoinPickup* SpawnCoinActorAtLocation(const FTransform& Transform, const TSubclassOf<ALyz_CoinPickup>& ActorClass);

private:
	void SpawnCoins();

	void HideCoins();

	TArray<ALyz_CoinPickup*> SpawnCoinsToScene(const TArray<TSubclassOf<ALyz_CoinPickup>>& CoinClasses);

};
