#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EventChannel.generated.h"

/**
 * Base class for event channels for EventSubsystem.
 */
UCLASS(BlueprintType)
class PROJECT_LYZANDRED_API UEventChannel : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Event Subsystem")
	FName ChannelId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Event Subsystem")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Event Subsystem")
	int32 MaxHistoryPerEvent = 10;
};
