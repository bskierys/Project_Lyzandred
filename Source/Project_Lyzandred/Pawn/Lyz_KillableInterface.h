#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Lyz_KillableInterface.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class ULyz_KillableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface to represent all pawns that are possible to kill (Player Character, Enemies, etc.)
 */
class PROJECT_LYZANDRED_API ILyz_KillableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Damage();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Kill();
};
