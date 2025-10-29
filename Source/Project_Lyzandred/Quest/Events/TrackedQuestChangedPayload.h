#pragma once

#include "CoreMinimal.h"
#include "Project_Lyzandred/Events/EventPayloadObject.h"
#include "TrackedQuestChangedPayload.generated.h"

class UQuest;

UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class PROJECT_LYZANDRED_API UTrackedQuestChangedPayload : public UEventPayloadObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UQuest* OldQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UQuest* NewQuest;
};
