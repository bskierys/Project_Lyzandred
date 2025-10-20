#include "Lyz_TriformCharacter.h"

#include "Ability/AbilityType.h"
#include "Form/FormDataAsset.h"
#include "Ability/Lyz_AbilityComponent.h"
#include "Ability/Lyz_AbilityManagerComponent.h"
#include "Project_Lyzandred/Character/Lyz_BlinkComponent.h"
#include "Project_Lyzandred/Game/Lyz_GameStateLibrary.h"
#include "Project_Lyzandred/PlayerController/Lyz_PlayerController.h"

void ALyz_TriformCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GameState = ULyz_GameStateLibrary::GetLyzGameState();
}

void ALyz_TriformCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

ALyz_TriformCharacter::ALyz_TriformCharacter()
{
	BlinkComponent = CreateDefaultSubobject<ULyz_BlinkComponent>(TEXT("Blinking Component"));
	AbilityManager = CreateDefaultSubobject<ULyz_AbilityManagerComponent>(TEXT("Ability Manager"));
}

void ALyz_TriformCharacter::Kill_Implementation()
{
	if (!IsValid(ControllerReference))
	{
		return;
	}
	ControllerReference->KillCurrentCharacter();
}

void ALyz_TriformCharacter::ApplyFormMovementConfiguration(const FFormMovementConfig MovementConfig)
{
	GetCharacterMovement()->MaxWalkSpeed = MovementConfig.MaxWalkSpeed;
	GetCharacterMovement()->JumpZVelocity = MovementConfig.JumpHeight;
	bCanDoubleJump = MovementConfig.bCanDoubleJump;
	bCanWallSlide = MovementConfig.bCanWallSlide;
	WallSlideGravityScale = MovementConfig.WallSlideSpeed;
	bCanWallJump = MovementConfig.bCanWallJump;
	WallJumpBounceImpulse = MovementConfig.WallJumpStrength;
	WallJumpVerticalImpulse = 2.f * MovementConfig.WallJumpStrength;
}

void ALyz_TriformCharacter::DeactivateActiveAbilities() const
{
	const auto ActiveAbilities = AbilityManager->GetAllActiveAbilities();
	
	for (const auto Ability : ActiveAbilities)
	{
		if (IsValid(Ability))
		{
			Ability->bIsEnabled = false;
			Ability->DeactivateAbility();
			Ability->OnAbilityDisabled();
		}
	}

	AbilityManager->ClearAbilities();
}

bool ALyz_TriformCharacter::InitializeNewFormAbilityComponent(UFormDataAsset* NewForm)
{
	if (!IsValid(NewForm))
	{
		return false;
	}
	
	for (const TPair<TSubclassOf<UAbilityType>, TSubclassOf<ULyz_AbilityComponent>>& Pair : NewForm->Abilities)
	{
		if (Pair.Value)
		{
			ULyz_AbilityComponent* NewAbility = NewObject<ULyz_AbilityComponent>(this, Pair.Value);
			NewAbility->RegisterComponent();
			NewAbility->bIsEnabled = true;
			NewAbility->OnAbilityEnabled();
			AbilityManager->RegisterAbility(Pair.Key, NewAbility);
		}
	}

	return true;
}

bool ALyz_TriformCharacter::SwitchForm_Implementation(UFormDataAsset* NewForm)
{
	if (!IsValid(NewForm))
	{
		UE_LOG(LogTemp, Error, TEXT("Can't switch form to nullptr"));
		return false;
	}

	if (!bSwitchingCharactersEnabled)
	{
		return false;
	}

	// start transition blink
	if (IsValid(BlinkComponent))
	{
		BlinkComponent->StartBlink(0.f, 0.1f, 2);
	}

	DeactivateActiveAbilities();
	
	const auto MovementConfig = NewForm->MovementConfig;
	ApplyFormMovementConfiguration(MovementConfig);

	const bool InitializeSuccessful = InitializeNewFormAbilityComponent(NewForm);

	// dispatch key event of changed form
	for (const auto Form: AvailableForms)
	{
		if (const auto KeyDefinition = Form->KeyDefinition; IsValid(KeyDefinition) && IsValid(GameState))
		{
			if (Form == NewForm && InitializeSuccessful)
			{
				GameState->SetKey(KeyDefinition, true);
			}
			else
			{
				GameState->SetKey(KeyDefinition, false);
			}
			
		}
	}

	if (!InitializeSuccessful)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't initialize abilities for new form"));
		return false;
	}
	
	CurrentFormData = NewForm;

	return true;
}

void ALyz_TriformCharacter::SwitchFormToIndex(const int32 Index)
{
	if (AvailableForms.IsEmpty())
	{
		return;
	}
	
	if (!AvailableForms.IsValidIndex(Index))
	{
		return;
	}

	CurrentFormIndex = Index;
	SwitchForm(AvailableForms[Index]);
}

void ALyz_TriformCharacter::SwitchCurrentFormByIndex(int32 Offset)
{
	const int32 NewIndex = GetCurrentFormIndexShiftedBy(Offset);
	if (NewIndex < 0)
	{
		return;
	}

	SwitchFormToIndex(NewIndex);
}

void ALyz_TriformCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

int32 ALyz_TriformCharacter::GetCurrentFormIndexShiftedBy(const int32 IndexShift) const
{
	if (AvailableForms.IsEmpty())
	{
		return -1;
	}
	
	const int32 IncrementedIndex = CurrentFormIndex + IndexShift;
	int32 ShiftedIndex = IncrementedIndex % AvailableForms.Num();

	if (ShiftedIndex < 0)
	{
		ShiftedIndex += AvailableForms.Num();
	}
	
	if (!AvailableForms.IsValidIndex(ShiftedIndex))
	{
		return -1;
	}
	
	return ShiftedIndex;
}
