#pragma once

#include "CoreMinimal.h"
#include "Lyz_UnlockReaction.generated.h"

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class PROJECT_LYZANDRED_API ULyz_UnlockReaction : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ExecuteReaction(AActor* Actor, bool bShouldUnlock);
};
