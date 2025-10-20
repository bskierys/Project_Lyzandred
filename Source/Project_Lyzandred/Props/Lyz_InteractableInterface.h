// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Lyz_InteractableInterface.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class ULyz_InteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_LYZANDRED_API ILyz_InteractableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void Interact(AActor* Caller, const FVector DirectionVector);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void OnInteractableChanged(const bool bInteractable);
};
