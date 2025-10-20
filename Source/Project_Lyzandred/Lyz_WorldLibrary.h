#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Lyz_WorldLibrary.generated.h"

UCLASS()
class PROJECT_LYZANDRED_API ULyz_WorldLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * @return Gets current UWorld needed for getting pawn and other statistics. Does all the needed null chacks to avoid
	 * crashing the game.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static UWorld* GetWorldSafe();
};
