#pragma once

#include "CoreMinimal.h"
#include "EventPayloadObject.generated.h"

/**
 * Class to carry the data with the event. Extend in C++ or in Blueprint to define your own payload.
 * Ideally, it should be struct, as they are lighter for Unreal, but I run out of time for iterating on this task and
 * this solution works.
 * 
 * Note to self: EditInlineNew allows construction in Blueprint. Use "Construct Object of Class" to create an instance.
 * Then set Properties. In C++ use NewObject<>().
 */
UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class PROJECT_LYZANDRED_API UEventPayloadObject : public UObject
{
	GENERATED_BODY()
};
