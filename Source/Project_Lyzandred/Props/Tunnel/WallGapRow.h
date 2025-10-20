#pragma once

#include "CoreMinimal.h"
#include "WallGapRow.generated.h"

USTRUCT(BlueprintType)
struct FWallGapRow
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<int32> SkipXIndices;
};