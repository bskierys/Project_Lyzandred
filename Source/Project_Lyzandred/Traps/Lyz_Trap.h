// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lyz_Trap.generated.h"

UCLASS(Blueprintable)
class PROJECT_LYZANDRED_API ALyz_Trap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALyz_Trap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Kill the Character
	UFUNCTION(BlueprintCallable, Category="Trap")
	void KillPawn(AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
