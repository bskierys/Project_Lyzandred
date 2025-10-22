#pragma once

#include "CoreMinimal.h"
#include "Project_Lyzandred/Other/SubsystemConfig.h"
#include "EventSubsystemConfig.generated.h"

class UEventChannel;

/**
 * Configuration for Event Subsystem. All Event Types must be registered to be able to be broadcasted.
 */
UCLASS(BlueprintType)
class PROJECT_LYZANDRED_API UEventSubsystemConfig : public USubsystemConfig
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TSet<UEventChannel*> RegisteredEvents;
};
