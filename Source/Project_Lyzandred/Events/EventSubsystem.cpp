#include "EventSubsystem.h"

#include "EventChannelObject.h"
#include "EventChannel.h"
#include "EventSubsystemConfig.h"
#include "Project_Lyzandred/Other/Lyz_DeveloperSettings.h"

DEFINE_LOG_CATEGORY(LyzEventSystem)

void UEventSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const ULyz_DeveloperSettings* Settings = GetDefault<ULyz_DeveloperSettings>();
	if (!Settings) 
	{
		UE_LOG(LyzEventSystem, Error, TEXT("ULyz_DeveloperSettings is empty"));
		return;
	}

	Config = Cast<UEventSubsystemConfig>(Settings->GetSubsystemConfigByClass(UEventSubsystemConfig::StaticClass()));
	if (Config) 
	{
		UE_LOG(LyzEventSystem, Log, TEXT("UEventSubsystemConfig config set correct"));
		for (const auto& Channel: Config->RegisteredEvents)
		{
			RegisterChannel(Channel);
		}
	}
	else 
	{
		UE_LOG(LyzEventSystem, Error, TEXT("UEventSubsystemConfig config set incorrect"));
	}
	
	UE_LOG(LyzEventSystem, Log, TEXT("EventSubsystem initialized"));
}

void UEventSubsystem::Deinitialize()
{
	for (const auto& Entry: ChannelMap)
	{
		Entry.Value->OnEvent.Clear();
	}

	UE_LOG(LyzEventSystem, Log, TEXT("EventSubsystem deinitialized"));
	Super::Deinitialize();
}

FName UEventSubsystem::ExtractChannelId(const UEventChannel* Channel)
{
	if (!IsValid(Channel))
	{
		return FName("null");
	}
	
	return Channel->ChannelId.IsNone() ? FName(*Channel->GetName()) : Channel->ChannelId;
}

void UEventSubsystem::RegisterChannel(UEventChannel* Channel)
{
	if (!IsValid(Channel))
	{
		UE_LOG(LyzEventSystem, Warning,
			TEXT("Attempted to register channel for null data asset %s"),
			*Channel->ChannelId.ToString()
		);
		return;
	}

	UEventChannelObject* ChannelObj = NewObject<UEventChannelObject>();
	const FName ChannelId = ExtractChannelId(Channel);
	ChannelObj->ChannelData = Channel;
	ChannelObj->ChannelId = ChannelId;

	ChannelMap.Add(ChannelId, ChannelObj);
	UE_LOG(LyzEventSystem, Log, TEXT("Registered Event Channel: %s"), *ChannelId.ToString());
}

void UEventSubsystem::SendEvent(UEventChannel* Channel, const FName EventTag, UObject* Sender, UEventPayloadObject* Payload)
{
	if (!IsValid(Channel))
	{
		return;
	}

	UEventChannelObject* ChannelObj = FindChannelObj(Channel);
	if (!ChannelObj)
	{
		UE_LOG(LyzEventSystem, Error, TEXT("Event could not be sent to channel: %s"), *Channel->ChannelId.ToString());
		return;
	}
	
	UE_LOG(LyzEventSystem, Log, TEXT("Sending Event to channel: %s"), *Channel->ChannelId.ToString());
	ChannelObj->Broadcast(EventTag, Sender, Payload);
}

UEventChannelObject* UEventSubsystem::GetEventChannel(UEventChannel* Channel) const
{
	if (!IsValid(Channel))
	{
		return nullptr;
	}

	const FName EventId = ExtractChannelId(Channel);
	if (const auto Found = ChannelMap.Find(EventId))
	{
		return *Found;
	}
	return nullptr;
}

UEventChannelObject* UEventSubsystem::FindChannelObj(const UEventChannel* Channel)
{
	const FName Id = ExtractChannelId(Channel);
	if (!ChannelMap.Contains(Id))
	{
		UE_LOG(LyzEventSystem, Error,
			TEXT("Channel: %s was not registered in the subsystem"),
			*Channel->ChannelId.ToString()
		);
		return nullptr;
	}
	return ChannelMap[Id];
}
