#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyStateAsset.generated.h"

UCLASS(BlueprintType)
class PROJECT_LYZANDRED_API UEnemyStateAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="State")
	FName StateName;
};
