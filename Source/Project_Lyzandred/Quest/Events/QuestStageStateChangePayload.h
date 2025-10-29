#pragma once

#include "CoreMinimal.h"
#include "Project_Lyzandred/Events/EventPayloadObject.h"
#include "Project_Lyzandred/Quest/QuestStructs.h"
#include "QuestStageStateChangePayload.generated.h"

class UQuest;
class UQuestStage;

UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class PROJECT_LYZANDRED_API UQuestStageStateChangePayload : public UEventPayloadObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UQuest* Quest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UQuestStage* QuestStage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StageIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestState OldState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestState NewState;
};
