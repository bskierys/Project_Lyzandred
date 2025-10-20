#pragma once

#include "CoreMinimal.h"
#include "AbilityDataAsset.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Lyz_AbilityComponent.generated.h"


class ALyz_TriformCharacter;

UCLASS(Abstract, Blueprintable, ClassGroup=(Custom))
class PROJECT_LYZANDRED_API ULyz_AbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULyz_AbilityComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	UAbilityDataAsset* AbilityData = nullptr;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Ability")
	void ActivateAbility();
	virtual void ActivateAbility_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Ability")
	void DeactivateAbility();
	virtual void DeactivateAbility_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category="Ability")
	bool CanBeActivated(const TSet<FName>& ActiveAbilities);
	virtual bool CanBeActivated_Implementation(const TSet<FName>& ActiveAbilities);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	bool bIsEnabled = false;
	
	/**
	* Called when ability becomes active (form switched in)
	*/
	UFUNCTION(BlueprintNativeEvent, Category="Ability")
	void OnAbilityEnabled();
	virtual void OnAbilityEnabled_Implementation();

	/**
	 * Called when form switches away
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Ability")
	void OnAbilityDisabled();
	virtual void OnAbilityDisabled_Implementation();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityActivationChanged, FName, AbilityName, bool, Active);

	UPROPERTY(BlueprintAssignable)
	FOnAbilityActivationChanged OnAbilityActivationChanged;

	UFUNCTION(BlueprintCallable, Category="Ability")
	void BroadcastAbilityActivationChanged(UAbilityDataAsset* ChangedAbilityData, const bool bActive = true);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character")
	ALyz_TriformCharacter* CharacterRef = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character")
	UCharacterMovementComponent* MovementComponentRef = nullptr;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
