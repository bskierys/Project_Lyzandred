// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lyz_CoinType.generated.h"

/**
 * Base object for the coinage type system.
 */
UCLASS(Blueprintable)
class PROJECT_LYZANDRED_API ULyz_CoinType : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "CoinType")
	FText Name = FText::FromString("Coin");

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "CoinType")
	int Value = 1;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "CoinType")
	USoundBase* PickupSound = nullptr;
};
