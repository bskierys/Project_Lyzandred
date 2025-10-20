// Fill out your copyright notice in the Description page of Project Settings.


#include "Lyz_Enemy.h"

#include "Lyz_EnemyMovementModeAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Project_Lyzandred/Character/Lyz_TriformCharacter.h"

// Sets default values
ALyz_Enemy::ALyz_Enemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALyz_Enemy::BeginPlay()
{
	Super::BeginPlay();
	DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void ALyz_Enemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnAttackEnds.Clear();
	OnAnimationEnd.Clear();

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ALyz_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALyz_Enemy::BroadcastAttackEnd()
{
	OnAttackEnds.Broadcast();
}

void ALyz_Enemy::SetMovementSpeedMode(ULyz_EnemyMovementModeAsset* NewMode)
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (!IsValid(NewMode))
	{
		return;
	}

	MovementComponent->MaxWalkSpeed = DefaultWalkSpeed * NewMode->SpeedMultiplier;
}

void ALyz_Enemy::BroadcastAnimationEnd(FName AnimationKey)
{
	OnAnimationEnd.Broadcast(AnimationKey);
}
