#pragma once

#include "CoreMinimal.h"
#include "QuestStructs.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestSubsystem.generated.h"

class UQuestStage;
class UEventChannelObject;
class UEventChannel;
class UQuest;
class UQuestSubsystemConfig;

DECLARE_LOG_CATEGORY_EXTERN(LyzQuestSystem, Log, All);

UCLASS(BlueprintType, Blueprintable)
class PROJECT_LYZANDRED_API UQuestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UPROPERTY(BlueprintReadOnly, Category="Quest Subsystem")
	UQuest* TrackedQuest;

	UFUNCTION(BlueprintCallable, Category="Quest Subsystem")
	TArray<UQuest*> GetQuestsWithState(EQuestState QuestState);

	UFUNCTION(BlueprintCallable, Category="Quest Subsystem")
	UQuest* GetQuestForId(FName QuestId);

	UFUNCTION(BlueprintCallable, Category="Quest Subsystem")
	void StartTrackingQuest(UQuest* Quest);

	inline static const FName NAME_EventQuestChanged = FName(TEXT("QuestStateChanged"));
	inline static const FName NAME_EventQuestStageChanged = FName(TEXT("QuestStageStateChanged"));
	inline static const FName NAME_TrackedQuestChange = FName(TEXT("TrackedQuestChanged"));

protected:
	UPROPERTY()
	UQuestSubsystemConfig* Config = nullptr;

	UPROPERTY()
	UEventChannelObject* QuestEventChannel = nullptr;

	UPROPERTY()
	TMap<FName, UQuest*> QuestMap;

	TMap<EQuestState, TArray<FName>> QuestStates;

	void HandleQuestActivated(UQuest* Quest);
	void HandleQuestCompleted(const UQuest* Quest);
	
	// below needs to be UFUNCTION to be able to use them for AddDynamic of the Delegate
	UFUNCTION()
	void OnQuestStateChanged(UQuest* Quest, EQuestState OldState, EQuestState NewState);
	
	UFUNCTION()
	void OnQuestStageStateChanged(UQuest* Quest, UQuestStage* QuestStage, int32 StageIndex, EQuestState OldState, EQuestState NewState);
};
