#pragma once

#include "CoreMinimal.h"
#include "QuestStage.h"
#include "QuestStructs.h"
#include "Quest.generated.h"

class UEventSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FQuestStateChanged,
	UQuest*, Quest,
	EQuestState, OldState,
	EQuestState, NewState
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(
	FQuestStageStateChanged,
	UQuest*, Quest,
	UQuestStage*, QuestStage,
	int32, StageIndex,
	EQuestState, OldState,
	EQuestState, NewState
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FQuestNewStage,
	UQuest*, Quest,
	UQuestStage*, NewStage
);

UCLASS(Abstract, Blueprintable, DefaultToInstanced, EditInlineNew)
class PROJECT_LYZANDRED_API UQuest : public UQuestBase
{
	GENERATED_BODY()
public:
#pragma region Properties
	UPROPERTY()
	int32 CurrentStageIndex = -1;
	
	UPROPERTY(EditAnywhere, Instanced,BlueprintReadWrite, Category="Quest Subsystem")
	TArray<UQuestStage*> Stages;
#pragma endregion
	
#pragma region Functions
	virtual void Init(UEventSubsystem* EventSystem) override;
	virtual void Clear_Implementation() override;
	virtual void ResetAndClear() override;

	/**
	 * Override this function to write logic for activating the Quest. When all the requirements are met, call
	 * `OnActivated` to proceed with the Quest.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Quest Subsystem")
	void ListenForActivation();
	virtual void ListenForActivation_Implementation();

	/**
	 * Needs to be called from ListenForActivation for the Quest to work.
	 */
	UFUNCTION(BlueprintCallable, Category="Quest Subsystem")
	void ActivateQuest();

	/**
	 * @return Currently Active Stage of the Quest or nullptr if Quest is Inactive.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Quest Subsystem")
	UQuestStage* GetCurrentStage() const;
	
#pragma endregion

#pragma region Delegates
	UPROPERTY(BlueprintAssignable, Category="Quest Subsystem")
	FQuestStateChanged OnQuestStateChanged;

	UPROPERTY(BlueprintAssignable, Category="Quest Subsystem")
	FQuestStageStateChanged OnQuestStageStateChanged;

	UPROPERTY(BlueprintAssignable, Category="Quest Subsystem")
	FQuestNewStage OnNewStage;
#pragma endregion

protected:
	TMap<FName, EQuestState> StagesStatesMap;
	
	UFUNCTION()
	void OnStageStateChanged(UQuestStage* QuestStage, EQuestState OldState, EQuestState NewState);

	virtual bool InternalChangeState(EQuestState NewState) override;
	
	void AdvanceToNextStage();
};
