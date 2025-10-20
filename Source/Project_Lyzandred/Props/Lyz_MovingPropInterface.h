#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Lyz_MovingPropInterface.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class ULyz_MovingPropInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_LYZANDRED_API ILyz_MovingPropInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Moving")
	void PlayMovement();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Moving")
	void ReverseMovement();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Moving")
	void PauseMovement();
};
