// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Lyz_PlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_LYZANDRED_API ALyz_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Character")
	void KillCurrentCharacter();
};
