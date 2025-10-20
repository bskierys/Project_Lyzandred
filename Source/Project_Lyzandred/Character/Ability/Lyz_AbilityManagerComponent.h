// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityDataAsset.h"
#include "Components/ActorComponent.h"
#include "Lyz_AbilityManagerComponent.generated.h"

class UAbilityType;
class ULyz_AbilityComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_LYZANDRED_API ULyz_AbilityManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULyz_AbilityManagerComponent();

	UFUNCTION(BlueprintCallable, Category="Forms")
	void RegisterAbility(TSubclassOf<UAbilityType> AbilityType, ULyz_AbilityComponent* Ability);

	UFUNCTION(BlueprintCallable, Category="Forms")
	void ClearAbilities();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Forms")
	TArray<ULyz_AbilityComponent*> GetAllActiveAbilities() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Forms")
	ULyz_AbilityComponent* GetActiveAbility(TSubclassOf<UAbilityType> AbilityType) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Forms")
	bool IsAbilityStateActive(UAbilityDataAsset* AbilityData) const;

	UFUNCTION(BlueprintCallable, Category="Forms")
	void ManualAbilityActivated(UAbilityDataAsset* AbilityData, bool bActive);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityActivationChanged, FName, AbilityName, bool, Active);

	UPROPERTY(BlueprintAssignable)
	FOnAbilityActivationChanged OnAbilityActivationChanged;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TSet<FName> ActiveStates;

	UPROPERTY()
	TMap<TSubclassOf<UAbilityType>, ULyz_AbilityComponent*> ActiveAbilities;

	UFUNCTION()
	void HandleAbilityActivationChanged(const FName AbilityName, const bool bActive);
};
