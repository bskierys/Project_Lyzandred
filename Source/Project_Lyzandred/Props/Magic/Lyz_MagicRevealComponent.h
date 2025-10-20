#pragma once

#include "CoreMinimal.h"
#include "Lyz_MagicalActorComponent.h"
#include "Components/ActorComponent.h"
#include "Lyz_MagicRevealComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_LYZANDRED_API ULyz_MagicRevealComponent : public ULyz_MagicalActorComponent
{
	GENERATED_BODY()

public:
	ULyz_MagicRevealComponent();

	virtual void ToggleWithMagic_Implementation() override;

	virtual void ActivateWithMagic_Implementation() override;

	virtual void DeactivateWithMagic_Implementation() override;

	virtual void OnToMagicForm_Implementation() override;

	virtual void OnFromMagicForm_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Magic")
	UMaterialInterface* TransparentMaterial = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Magic")
	bool bIsSolid = false;

protected:
	virtual void BeginPlay() override;
	
private:
	
	UFUNCTION()
	void SetRevealed(bool bRevealed);

	UFUNCTION()
	void RefreshRevealState(bool bNewSolid);

	UFUNCTION()
	void SetCollisionSolid(bool bSolid, bool bMagicVisible);
};
