#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Project_Lyzandred/Pickup/Key/Lyz_KeyDefinition.h"
#include "Lyz_GameState.generated.h"

UCLASS(Blueprintable)
class PROJECT_LYZANDRED_API ALyz_GameState : public AGameState
{
	GENERATED_BODY()
	
public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, bool> KeyValues;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetKey(ULyz_KeyDefinition* Key, bool bValue);
	virtual void SetKey_Implementation(ULyz_KeyDefinition* Key, bool bValue);

	UFUNCTION(BlueprintCallable)
	bool GetKey(FName Id) const;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKeyChanged, FName, Key, bool, Value);

	UPROPERTY(BlueprintAssignable)
	FOnKeyChanged OnKeyChanged;
};
