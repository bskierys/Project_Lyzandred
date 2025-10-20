#include "Lyz_AbilityComponent.h"
#include "Project_Lyzandred/Character/Lyz_TriformCharacter.h"

ULyz_AbilityComponent::ULyz_AbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULyz_AbilityComponent::ActivateAbility_Implementation()
{
	if (IsValid(AbilityData))
	{
		OnAbilityActivationChanged.Broadcast(AbilityData->Name, true);
	}
}

void ULyz_AbilityComponent::DeactivateAbility_Implementation()
{
	if (IsValid(AbilityData))
	{
		OnAbilityActivationChanged.Broadcast(AbilityData->Name, false);
	}
}

bool ULyz_AbilityComponent::CanBeActivated_Implementation(const TSet<FName>& ActiveAbilities)
{
	return true;
}

void ULyz_AbilityComponent::OnAbilityEnabled_Implementation()
{
}

void ULyz_AbilityComponent::OnAbilityDisabled_Implementation()
{
}

void ULyz_AbilityComponent::BroadcastAbilityActivationChanged(UAbilityDataAsset* ChangedAbilityData, const bool bActive)
{
	if (IsValid(ChangedAbilityData))
	{
		OnAbilityActivationChanged.Broadcast(ChangedAbilityData->Name, bActive);
	}
	else if (IsValid(AbilityData))
	{
		OnAbilityActivationChanged.Broadcast(AbilityData->Name, bActive);
	}
}

void ULyz_AbilityComponent::BeginPlay()
{
	Super::BeginPlay();
	
	const auto Owner = GetOwner();
	if (!IsValid(Owner)  || !Owner->IsA(ALyz_TriformCharacter::StaticClass()))
	{
		// TODO: Remove tight coupling
		UE_LOG(LogTemp, Error, TEXT("Abilities can be attached only to Lyz_TriformCharacter"));
		return;
	}
	
	CharacterRef = Cast<ALyz_TriformCharacter>(Owner);
	if (!IsValid(CharacterRef))
	{
		return;
	}
	MovementComponentRef = CharacterRef->GetCharacterMovement();
}

void ULyz_AbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
