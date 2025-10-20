#pragma once

#include "CoreMinimal.h"
#include "Lyz_MagicTogglableInterface.h"
#include "Components/ActorComponent.h"
#include "Lyz_MagicalActorComponent.generated.h"

class UFormDataAsset;
class ALyz_GameState;

USTRUCT(Blueprintable)
struct FPrimitiveComponentInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UPrimitiveComponent> Component = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<ECollisionEnabled::Type> CollisionEnabled = ECollisionEnabled::QueryAndPhysics;

	UPROPERTY(BlueprintReadWrite)
	FCollisionResponseContainer Responses = FCollisionResponseContainer::GetDefaultResponseContainer();

	UPROPERTY(BlueprintReadWrite)
	bool bCastShadow = true;

	UPROPERTY(BlueprintReadWrite)
	bool bGeneratesOverlapEvents = true;
	
	UPROPERTY(BlueprintReadWrite)
	UMaterialInterface* OriginalMaterial = nullptr;
};

UCLASS(Blueprintable, Abstract, ClassGroup=(Custom))
class PROJECT_LYZANDRED_API ULyz_MagicalActorComponent : public UActorComponent, public ILyz_MagicTogglableInterface
{
	GENERATED_BODY()

public:
	ULyz_MagicalActorComponent();

	UPROPERTY(BlueprintReadWrite, Category="Game")
	ALyz_GameState* GameStateRef = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Magic")
	UFormDataAsset* MagicFormAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Magic")
	UMaterialInterface* MagicalOverlayMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Magic")
	float GlowIntensity = 2.f;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category="Magic")
	TArray<FPrimitiveComponentInfo> PrimitiveComponents;

	UPROPERTY(BlueprintReadWrite, Category="Magic")
	UMaterialInstanceDynamic* GlowingOverlay = nullptr;

	UPROPERTY(BlueprintReadWrite, Category="Magic")
	bool bIsInMagicForm = false;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Magic")
	void OnToMagicForm();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Magic")
	void OnFromMagicForm();

private:
	UFUNCTION()
	void HandleOnKeyChanged(FName Key, bool bValue);
};
