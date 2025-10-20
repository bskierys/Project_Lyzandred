#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Project_Lyzandred/Pickup/Key/Lyz_KeyDefinition.h"
#include "FormDataAsset.generated.h"


class UAbilityType;
class ULyz_AbilityComponent;

USTRUCT(BlueprintType)
struct FFormMovementConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float MaxWalkSpeed = 600.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float JumpHeight = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	bool bCanDoubleJump = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	bool bCanWallJump = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	bool bCanWallSlide = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float WallSlideSpeed = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float WallJumpStrength = 600;
};

USTRUCT(BlueprintType)
struct FFormVisuals
{
	GENERATED_BODY()

	/**
	 * Skeletal mesh for this form
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Form|Visual")
	TObjectPtr<USkeletalMesh> Mesh = nullptr;

	/**
	 * Animations to showcase form
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Form|Visual")
	TArray<UAnimMontage*> ShowcaseAnimations;

	/**
	 * Anim blueprint to use with this form
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Form|Visual")
	TSubclassOf<UAnimInstance> AnimClass = nullptr;
};

UENUM(BlueprintType)
enum class EAccessoryType : uint8
{
	RightHandAccessory = 0   UMETA(DisplayName = "Right Hand Accessory"),
	LeftHandAccessory = 1     UMETA(DisplayName = "Left Hand Accessory"),
};

/**
 * Data Asset describing a character form (Knight, Rogue, Mage).
 * Contains movement config, visuals and a map of abilities.
 */
UCLASS(BlueprintType)
class PROJECT_LYZANDRED_API UFormDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Form")
	FName FormName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Form")
	FFormMovementConfig MovementConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Form")
	TMap<TSubclassOf<UAbilityType>, TSubclassOf<ULyz_AbilityComponent>> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Form")
	FFormVisuals Visuals;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Form")
	TMap<EAccessoryType, UStaticMesh*> Accessories;
	
	/**
	 * Key that the world can react to when changed to this form (both on event dispatcher and static check).
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Key")
	ULyz_KeyDefinition* KeyDefinition = nullptr;
};

