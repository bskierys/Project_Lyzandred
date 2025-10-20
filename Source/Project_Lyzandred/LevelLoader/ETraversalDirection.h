#pragma once

#include "CoreMinimal.h"
#include "ETraversalDirection.generated.h"

UENUM(BlueprintType)
enum class ETraversalDirection : uint8
{
	Returned = 0   UMETA(DisplayName = "Returned"),
	Forward = 1     UMETA(DisplayName = "Forward"),
	Backward = 2   UMETA(DisplayName = "Backward")
};
