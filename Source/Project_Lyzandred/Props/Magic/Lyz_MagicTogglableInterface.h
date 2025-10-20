#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Lyz_MagicTogglableInterface.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class ULyz_MagicTogglableInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_LYZANDRED_API ILyz_MagicTogglableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Magic")
	void ToggleWithMagic();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Magic")
	void ActivateWithMagic();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Magic")
	void DeactivateWithMagic();
};
