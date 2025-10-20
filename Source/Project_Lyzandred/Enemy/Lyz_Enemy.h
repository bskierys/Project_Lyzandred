// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Project_Lyzandred/Pawn/Lyz_KillableInterface.h"
#include "Lyz_Enemy.generated.h"

class ULyz_EnemyMovementModeAsset;
class ULyz_PassiveEnemyBehaviour;

UCLASS(Abstract, Blueprintable)
class PROJECT_LYZANDRED_API ALyz_Enemy : public ACharacter, public ILyz_KillableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALyz_Enemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent ,BlueprintCallable)
	void Attack();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEnds);

	UPROPERTY(BlueprintAssignable)
	FOnAttackEnds OnAttackEnds;

	UFUNCTION(BlueprintCallable)
	void BroadcastAttackEnd();
	
	UFUNCTION(BlueprintCallable)
	void SetMovementSpeedMode(ULyz_EnemyMovementModeAsset* NewMode);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ChangeAlertedState(bool bNoticeActive, bool bWithAnimation);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlaySpawnAnimation();
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bIsAlerted = false;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bIsDead = false;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimationEnd, FName, AnimationKey);

	UPROPERTY(BlueprintAssignable)
	FOnAnimationEnd OnAnimationEnd;

	UFUNCTION(BlueprintCallable)
	void BroadcastAnimationEnd(FName AnimationKey);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	ULyz_PassiveEnemyBehaviour* PassiveBehaviour = nullptr;

private:
	UPROPERTY()
	float DefaultWalkSpeed = .0f;
};
