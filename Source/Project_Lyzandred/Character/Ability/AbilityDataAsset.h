#pragma once

#include "CoreMinimal.h"
#include "AbilityType.h"
#include "Engine/DataAsset.h"
#include "AbilityDataAsset.generated.h"

UCLASS(Blueprintable)
class PROJECT_LYZANDRED_API UAbilityDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "Ability")
	FName Name = FName("Ability");

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "Ability")
	TSubclassOf<UAbilityType> AbilityType = nullptr;
};
