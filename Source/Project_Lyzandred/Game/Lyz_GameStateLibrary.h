#pragma once

#include "CoreMinimal.h"
#include "Lyz_GameState.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Lyz_GameStateLibrary.generated.h"

class UFormDataAsset;

UCLASS()
class PROJECT_LYZANDRED_API ULyz_GameStateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static ALyz_GameState* GetLyzGameState();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool IsCharacterInForm(const UFormDataAsset* FormData, const TMap<FName, bool> KeyValues);
};
