#pragma once

#include "CoreMinimal.h"
#include "Project_Lyzandred/Other/SubsystemConfig.h"
#include "QuestSubsystemConfig.generated.h"

class UEventChannel;
class UQuest;
/**
 * 
 */
UCLASS(BlueprintType)
class PROJECT_LYZANDRED_API UQuestSubsystemConfig : public USubsystemConfig
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UEventChannel* QuestEventChannel;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Instanced)
	TArray<UQuest*> Quests;
};
