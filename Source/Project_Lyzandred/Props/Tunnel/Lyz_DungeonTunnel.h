// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lyz_DungeonBase.h"
#include "WallGapRow.h"
#include "Lyz_DungeonTunnel.generated.h"

UCLASS()
class PROJECT_LYZANDRED_API ALyz_DungeonTunnel : public ALyz_DungeonBase
{
	GENERATED_BODY()

public:	
	ALyz_DungeonTunnel();

protected:
	virtual void BeginPlay() override;
	void GenerateWallMeshes(float TileSize, float BaseZ);

	virtual void OnConstruction(const FTransform& Transform) override;

public:
	UPROPERTY(EditAnywhere, Category="Tunnel")
	TMap<int32, FWallGapRow> LeftWallGaps;

	UPROPERTY(EditAnywhere, Category="Tunnel")
	TMap<int32, FWallGapRow> RightWallGaps;
};
