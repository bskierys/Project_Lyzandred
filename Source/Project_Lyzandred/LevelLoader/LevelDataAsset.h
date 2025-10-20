#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelDataAsset.generated.h"

UCLASS(BlueprintType)
class PROJECT_LYZANDRED_API ULevelDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Level")
	FName LevelName = FName("Level");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Level")
	TSet<TSoftObjectPtr<UWorld>> Sublevels;
};
