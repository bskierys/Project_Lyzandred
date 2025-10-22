#include "EventChannelObject.h"

#include "EventChannel.h"
#include "EventSubsystem.h"
// Do not remove the below include even if the IDE says it's unused. Necessary for the compiler to know that this is
// extending UObject and can be used in TWeakPointer 
#include "EventPayloadObject.h"

void UEventChannelObject::Broadcast(const FName EventTag, UObject* Sender, UEventPayloadObject* Payload)
{
	SaveEventToHistory(EventTag ,Sender, Payload);
	OnEvent.Broadcast(EventTag ,Sender, Payload);
}

void UEventChannelObject::SaveEventToHistory(const FName EventTag, UObject* Sender, UEventPayloadObject* Payload)
{
	// save to history
	FEventRecord Rec;
	Rec.EventTag = EventTag;
	Rec.Sender = Sender;
	Rec.Payload = Payload;
	Rec.Timestamp = FDateTime::UtcNow();
	History.Add(Rec);

	// history limit, remove last
	const int32 MaxHistoryPerEvent = ChannelData->MaxHistoryPerEvent;
	if (MaxHistoryPerEvent > 0 && History.Num() > MaxHistoryPerEvent)
	{
		UE_LOG(LyzEventSystem, Log,
			   TEXT("Max history for event: %s exceeded. Removing history."),
			   *ChannelData->ChannelId.ToString()
		);
		const int32 ToRemove = History.Num() - MaxHistoryPerEvent;
		History.RemoveAt(0, ToRemove, EAllowShrinking::No);
	}
}
