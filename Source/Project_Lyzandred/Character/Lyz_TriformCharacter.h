#pragma once

#include "CoreMinimal.h"
#include "Form/FormDataAsset.h"
#include "Project_Lyzandred/Game/Lyz_GameState.h"
#include "GameFramework/Character.h"
#include "Project_Lyzandred/Pawn/Lyz_KillableInterface.h"
#include "Lyz_TriformCharacter.generated.h"

enum class EAccessoryType : uint8;
class ALyz_PlayerController;
class UFormDataAsset;
class ULyz_AbilityManagerComponent;
class ULyz_BlinkComponent;

/**
 * Class for character that can change forms fluently. Should replace original character after reaching basic
 * capabilities.
 */
UCLASS(Abstract, Blueprintable)
class PROJECT_LYZANDRED_API ALyz_TriformCharacter : public ACharacter, public ILyz_KillableInterface 
{
	GENERATED_BODY()
	
protected:
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Forms")
	int32 CurrentFormIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Forms")
	TArray<UFormDataAsset*> AvailableForms;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ULyz_BlinkComponent* BlinkComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ULyz_AbilityManagerComponent* AbilityManager = nullptr;
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:
	ALyz_TriformCharacter();

	virtual void Kill_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Forms")
	UFormDataAsset* CurrentFormData = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Game")
	ALyz_PlayerController* ControllerReference = nullptr;

	/**
	 * Switches the character to a new form. Applies abilities and form config.
	 * Remember that Movement config should be applied before abilities for them
	 * to work as they rely on these values.
	 * @param NewForm 
	 * @return Whether the switch was successful.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Forms")
	bool SwitchForm(UFormDataAsset* NewForm);
	virtual bool SwitchForm_Implementation(UFormDataAsset* NewForm);

	UFUNCTION(BlueprintCallable, Category="Forms")
	void SwitchFormToIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category="Forms")
	void SwitchCurrentFormByIndex(int32 Offset);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * Smoothly animate the camera to a desired offset.
	 * @param Offset 
	 * @param Reversed If effect should be reversed (e.g., when switching ability off).
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Forms")
	void AnimateCameraOffset(const FVector Offset, const bool Reversed);

	/**
	 * Switches on/off the light carried with character.
	 * @param Visible 
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Forms")
	void SetLightVisibility(const bool Visible);

	UPROPERTY(BlueprintReadWrite, Category="Input")
	bool bMovementInputEnabled = true;

	UPROPERTY(BlueprintReadWrite, Category="Input")
	bool bSwitchingCharactersEnabled = true;

	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintImplementableEvent, Category="Accessories")
	UPrimitiveComponent* GetAccessoryComponent(EAccessoryType AccessoryType) const;

protected:
	/**
	 * The current form index shifted by a value (modulo length of available ones).
	 * @param IndexShift 
	 * @return -1 if can't find a valid Index.
	 */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category="Forms")
	int32 GetCurrentFormIndexShiftedBy(const int32 IndexShift) const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Game")
	ALyz_GameState* GameState = nullptr;

	// Advanced Movement Config
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="DoubleJump")
	bool bCanDoubleJump = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="WallJump")
	bool bCanWallJump = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="WallJump")
	float WallJumpBounceImpulse = 600.f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="WallJump")
	float WallJumpVerticalImpulse = 1200.f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="WallSlide")
	bool bCanWallSlide = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="WallSlide")
	float WallSlideGravityScale = 0.6f;

	void ApplyFormMovementConfiguration(FFormMovementConfig MovementConfig);
	void DeactivateActiveAbilities() const;
	bool InitializeNewFormAbilityComponent(UFormDataAsset* NewForm);
};
