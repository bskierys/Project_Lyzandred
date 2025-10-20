#pragma once

#include "CoreMinimal.h"
#include "AbilityType.generated.h"

UCLASS(Blueprintable)
class PROJECT_LYZANDRED_API UAbilityType : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText Name = FText::FromString("Primary");
};
