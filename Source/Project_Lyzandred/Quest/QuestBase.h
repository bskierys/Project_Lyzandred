#pragma once

#include "CoreMinimal.h"
#include "QuestStructs.h"
#include "QuestBase.generated.h"

class UEventSubsystem;

/**
 * Base class for Quest Objects: Quest and Quest Stages.
 */
UCLASS(Abstract, DefaultToInstanced, EditInlineNew)
class PROJECT_LYZANDRED_API UQuestBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quest Subsystem")
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quest Subsystem")
	FQuestDescription Description;

	UPROPERTY(BlueprintReadOnly, Category="Quest Subsystem")
	EQuestState State = EQuestState::Inactive;

	UPROPERTY(BlueprintReadOnly, Category="Quest Subsystem")
	UEventSubsystem* EventSubsystem = nullptr;

	UFUNCTION()
	virtual void Init(UEventSubsystem* EventSystem);
	
	/**
    * Resets the state of the Quest entirely. Sets it to inactive so it is possible to complete it again.
    * Use with caution.
    */
	UFUNCTION(BlueprintCallable, Category="Quest Subsystem")
	virtual void ResetAndClear();

	/**
	* Perform a cleanup of the listeners to avoid memory leaks. Override to perform your own cleanup in the Quest Stage.
	* Always call `Super`. Called by the same method of `Quest`.
	*/
	UFUNCTION(BlueprintNativeEvent, Category="Quest Subsystem")
	void Clear();
	virtual void Clear_Implementation();

protected:
	virtual bool InternalChangeState(EQuestState NewState);
};
