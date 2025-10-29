#pragma once

#include "CoreMinimal.h"
#include "QuestBase.h"
#include "QuestStructs.h"
#include "QuestStage.generated.h"

class UEventSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FStageStateChanged,
	UQuestStage*, QuestStage,
	EQuestState, OldState,
	EQuestState, NewState
);

UCLASS(Abstract, Blueprintable, DefaultToInstanced, EditInlineNew)
class PROJECT_LYZANDRED_API UQuestStage : public UQuestBase
{
	GENERATED_BODY()

public:
	virtual void Init(UEventSubsystem* EventSystem) override;
	virtual void Clear_Implementation() override;
	
	UFUNCTION(BlueprintCallable, Category="Quest Subsystem")
	void Activate();

	UFUNCTION(BlueprintNativeEvent, Category="Quest Subsystem")
	void ListenForCompletion();
	virtual void ListenForCompletion_Implementation();

	UFUNCTION(BlueprintCallable, Category="Quest Subsystem")
	void CompleteStage();

	UPROPERTY(BlueprintAssignable, Category="Quest Subsystem")
	FStageStateChanged OnStageStateChanged;

protected:
	virtual bool InternalChangeState(EQuestState NewState) override;
};
