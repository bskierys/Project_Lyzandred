#pragma once

#include "CoreMinimal.h"
#include "EventChannelObject.generated.h"

class UEventPayloadObject;
class UEventChannel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FOnEvent,
	FName, EventTag,
	UObject*, Sender,
	UEventPayloadObject*, Payload
);

/**
 * History record.
 */
USTRUCT(BlueprintType)
struct FEventRecord
{
	GENERATED_BODY()

	UPROPERTY()
	FName EventTag;

	UPROPERTY()
	TWeakObjectPtr<UObject> Sender;

	UPROPERTY()
	TWeakObjectPtr<UEventPayloadObject> Payload;

	UPROPERTY()
	FDateTime Timestamp;
};

/**
 * Designed to keep everything by event type (history, listeners, etc).
 */
UCLASS()
class PROJECT_LYZANDRED_API UEventChannelObject : public UObject
{
	GENERATED_BODY()
public:
	/**
	 * Duplication from ChannelData but useful for quick lookups.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Event")
	FName ChannelId = FName();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Event Subsystem")
	UEventChannel* ChannelData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Event Subsystem")
	TArray<FEventRecord> History;

	UPROPERTY(BlueprintAssignable, Category="Event Subsystem")
	FOnEvent OnEvent;

	UFUNCTION(BlueprintCallable, Category="Event Subsystem")
	void Broadcast(FName EventTag, UObject* Sender, UEventPayloadObject* Payload);

protected:
	void SaveEventToHistory(FName EventTag, UObject* Sender, UEventPayloadObject* Payload);
};
