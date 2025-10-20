#pragma once

#include "CoreMinimal.h"
#include "Lyz_KeyDefinition.h"
#include "GameFramework/Actor.h"
#include "Project_Lyzandred/Game/Lyz_GameState.h"
#include "Lyz_Key.generated.h"

UCLASS()
class PROJECT_LYZANDRED_API ALyz_Key : public AActor
{
	GENERATED_BODY()
	
public:	
	ALyz_Key();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	ALyz_GameState* GameStateRef = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Key")
	UStaticMesh* KeyMesh = nullptr;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Key")
	ULyz_KeyDefinition* KeyDefinition = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Key")
	USoundBase* CollectSound = nullptr;

	UFUNCTION(BlueprintCallable, Category="Key")
	void CollectKey(AActor* OtherActor);
};
