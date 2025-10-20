#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Lyz_EnemyMovementModeAsset.generated.h"

UCLASS(Blueprintable)
class PROJECT_LYZANDRED_API ULyz_EnemyMovementModeAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MovementMode")
	FName MovementModeName = FName("Walking");;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MovementMode")
	float SpeedMultiplier = 1.f;
};
