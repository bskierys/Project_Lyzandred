#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EventSubsystem.generated.h"

class UEventPayloadObject;
class UEventSubsystemConfig;
class UEventChannelObject;
class UEventChannel;

DECLARE_LOG_CATEGORY_EXTERN(LyzEventSystem, Log, All);

UCLASS(BlueprintType, Blueprintable)
class PROJECT_LYZANDRED_API UEventSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

#pragma region API
	/**
	 * Send Event into a system.
	 * @param Channel
	 * @param EventTag 
	 * @param Sender 
	 * @param Payload 
	 */
	UFUNCTION(BlueprintCallable, Category="Event Subsystem")
	void SendEvent(UEventChannel* Channel, FName EventTag, UObject* Sender, UEventPayloadObject* Payload);

	/**
	 * Get Events Channel. Allows for subscribing to events and history.
	 * Channels can be as granular as a single event type per channel or as broad as a single channel for the whole
	 * project.
	 * @param Channel 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Event Subsystem")
	UEventChannelObject* GetEventChannel(UEventChannel* Channel) const;
	
#pragma endregion

protected:
	UPROPERTY()
	TMap<FName, UEventChannelObject*> ChannelMap;

	UPROPERTY()
	UEventSubsystemConfig* Config = nullptr;

	UEventChannelObject* FindChannelObj(const UEventChannel* Channel);
	static FName ExtractChannelId(const UEventChannel* Channel);
	void RegisterChannel(UEventChannel* Channel);
};
