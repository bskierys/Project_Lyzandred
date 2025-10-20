// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Lyz_BlinkComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_LYZANDRED_API ULyz_BlinkComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULyz_BlinkComponent();

	/**
	 * Start blinking on the owning actor.
	 * @param DelayBeforeFirstBlink 
	 * @param TimeBetweenBlinks 
	 * @param NumberOfBlinks 
	 */
	UFUNCTION(BlueprintCallable, Category="Blink")
	void StartBlink(float DelayBeforeFirstBlink, float TimeBetweenBlinks, int32 NumberOfBlinks);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	FTimerHandle BlinkTimerHandle;

	// blink config copied from a start method
	UPROPERTY()
	float InDelayBeforeFirstBlink = 0.f;
	UPROPERTY()
	float InTimeBetweenBlinks = 0.2f;
	UPROPERTY()
	int32 InNumberOfBlinks = 2;

	// Current blink state
	UPROPERTY()
	int32 BlinkCount = 0;
	UPROPERTY()
	bool bIsBlinking = false;

	UFUNCTION()
	void HandleBlink();

	UFUNCTION()
	UMeshComponent* GetMeshComponent() const;
};
