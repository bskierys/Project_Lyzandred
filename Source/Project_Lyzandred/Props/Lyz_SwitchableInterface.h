#pragma once

#include "UObject/Interface.h"
#include "Lyz_SwitchableInterface.generated.h"

UINTERFACE(Blueprintable)
class PROJECT_LYZANDRED_API ULyz_SwitchableInterface : public UInterface
{
	GENERATED_BODY()
};

class ILyz_SwitchableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Reaction")
	void SwitchOn();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Reaction")
	void SwitchOff();
};
