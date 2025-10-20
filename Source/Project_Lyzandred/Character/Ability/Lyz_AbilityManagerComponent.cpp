#include "Lyz_AbilityManagerComponent.h"
#include "Lyz_AbilityComponent.h"

ULyz_AbilityManagerComponent::ULyz_AbilityManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULyz_AbilityManagerComponent::RegisterAbility(TSubclassOf<UAbilityType> AbilityType, ULyz_AbilityComponent* Ability)
{
	ActiveAbilities.Add(AbilityType, Ability);
	Ability->OnAbilityActivationChanged.AddDynamic(this, &ULyz_AbilityManagerComponent::HandleAbilityActivationChanged);
}

void ULyz_AbilityManagerComponent::ClearAbilities()
{
	for (const auto AbilityPair : ActiveAbilities)
	{
		if (const auto Ability = AbilityPair.Value; IsValid(Ability))
		{
			Ability->bIsEnabled = false;
			Ability->DeactivateAbility();
			Ability->OnAbilityDisabled();
			Ability->OnAbilityActivationChanged.RemoveDynamic(this, &ULyz_AbilityManagerComponent::HandleAbilityActivationChanged);
		}
	}
	
	ActiveAbilities.Empty();
	ActiveStates.Empty();
}

TArray<ULyz_AbilityComponent*> ULyz_AbilityManagerComponent::GetAllActiveAbilities() const
{
	TArray<ULyz_AbilityComponent*> Abilities;
	ActiveAbilities.GenerateValueArray(Abilities);
	return Abilities;
}

ULyz_AbilityComponent* ULyz_AbilityManagerComponent::GetActiveAbility(const TSubclassOf<UAbilityType> AbilityType) const
{
	ULyz_AbilityComponent* ActiveAbility = ActiveAbilities.FindRef(AbilityType);
	if (!IsValid(ActiveAbility))
	{
		return nullptr;
	}

	return ActiveAbility;
}

bool ULyz_AbilityManagerComponent::IsAbilityStateActive(UAbilityDataAsset* AbilityData) const
{
	if (!IsValid(AbilityData))
	{
		return false;
	}
	
	if (ActiveStates.Contains(AbilityData->Name))
	{
		return true;
	}

	return false;
}

void ULyz_AbilityManagerComponent::ManualAbilityActivated(UAbilityDataAsset* AbilityData, bool bActive)
{
	if (!IsValid(AbilityData))
	{
		return;
	}

	HandleAbilityActivationChanged(AbilityData->Name, bActive);
}

void ULyz_AbilityManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULyz_AbilityManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULyz_AbilityManagerComponent::HandleAbilityActivationChanged(const FName StateName, const bool bActive)
{
	const bool bPrevState = ActiveStates.Contains(StateName);
	if (bActive)
	{
		ActiveStates.Add(StateName);
	}
	else
	{
		ActiveStates.Remove(StateName);
	}
	if (bPrevState != bActive)
	{
		OnAbilityActivationChanged.Broadcast(StateName, bActive);
	}
}

