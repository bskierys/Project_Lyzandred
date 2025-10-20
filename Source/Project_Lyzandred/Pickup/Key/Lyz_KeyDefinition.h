#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Lyz_KeyDefinition.generated.h"

UCLASS(BlueprintType)
class PROJECT_LYZANDRED_API ULyz_KeyDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName KeyId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText LockedReason;
};
