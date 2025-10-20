// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lyz_TriformCharacter.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Lyz_CharacterLibrary.generated.h"

/**
 * Function Library to handle operations around `Lyz_Character`. Remember that it holds reference to Lyz_Character, so
 * avoid putting methods not related to `Lyz_Character` here.
 */
UCLASS()
class PROJECT_LYZANDRED_API ULyz_CharacterLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * The method checks if passed Actor is current Player Pawn.
	 * @param Actor Actor to check
	 * @return if current player pawn
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Character")
	static bool CheckIfCurrentPlayerPawn(AActor* Actor);

	/**
	 * Cast an instance of Actor as Lyz_Character. Caution: Does casting.
	 * @return Lyz_Character
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Character")
	static ALyz_TriformCharacter* GetPlayerPawnAsTriformCharacter();
};
