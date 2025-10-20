// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lyz_CoinPickup.generated.h"

UCLASS(Abstract, Blueprintable)
class PROJECT_LYZANDRED_API ALyz_CoinPickup : public AActor
{
	GENERATED_BODY()

public:
	ALyz_CoinPickup();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Visibility")
	void AnimateCoinSpawn(const float Delay);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Visibility")
	void Hide();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Visibility")
	void Show();
};
