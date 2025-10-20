#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lyz_DungeonBase.generated.h"

UCLASS(Abstract)
class PROJECT_LYZANDRED_API ALyz_DungeonBase : public AActor
{
	GENERATED_BODY()

public:	
	ALyz_DungeonBase();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void SetupMeshComponents();

	void GenerateFloorMeshes(float TileSize, float BaseZ) const;

public:
	UPROPERTY(EditAnywhere, Category="Dungeon")
	int32 HeightInSections = 2;

	UPROPERTY(EditAnywhere, Category="Dungeon")
	int32 LengthInSections = 5;

	UPROPERTY(EditAnywhere, Category="Dungeon")
	int32 WidthInSections = 2;

	UPROPERTY(EditAnywhere, Category="Dungeon")
	int32 ElevationInSections = 1;

	UPROPERTY(EditAnywhere, Category="Meshes")
	UStaticMesh* WallMesh = nullptr;

	UPROPERTY(EditAnywhere, Category="Meshes")
	UStaticMesh* FloorMesh = nullptr;

	UPROPERTY(EditAnywhere, Category="Meshes")
	UStaticMesh* SupportMesh = nullptr;

protected:
	UPROPERTY()
	UInstancedStaticMeshComponent* Walls = nullptr;

	UPROPERTY()
	UInstancedStaticMeshComponent* Floors = nullptr;

	UPROPERTY()
	UInstancedStaticMeshComponent* Supports = nullptr;
};
