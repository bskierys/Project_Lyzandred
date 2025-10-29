#pragma once

#include "CoreMinimal.h"
#include "Project_Lyzandred/Events/EventPayloadObject.h"
#include "Project_Lyzandred/Quest/QuestStructs.h"
#include "QuestStateChangePayload.generated.h"

class UQuest;

UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class PROJECT_LYZANDRED_API UQuestStateChangePayload : public UEventPayloadObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UQuest* Quest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestState OldState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestState NewState;
};
