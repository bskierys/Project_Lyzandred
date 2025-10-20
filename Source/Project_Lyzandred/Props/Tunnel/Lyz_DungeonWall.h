#pragma once

#include "CoreMinimal.h"
#include "Lyz_DungeonWall.generated.h"

UCLASS()
class PROJECT_LYZANDRED_API ALyz_DungeonWall : public AActor
{
	GENERATED_BODY()

public:
	ALyz_DungeonWall();

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:
	UPROPERTY(EditAnywhere, Category="Dungeon")
	int32 WallLength = 5;

	UPROPERTY(EditAnywhere, Category="Dungeon")
	int32 WallHeight = 2;

	UPROPERTY(EditAnywhere, Category="Meshes")
	UStaticMesh* WallMesh = nullptr;

private:
	UPROPERTY()
	UInstancedStaticMeshComponent* Walls = nullptr;

	virtual void SetupMeshComponents();

	void GenerateWallMeshes(float TileSize) const;
};
