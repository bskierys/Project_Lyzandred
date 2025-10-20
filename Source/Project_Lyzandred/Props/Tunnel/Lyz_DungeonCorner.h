#pragma once

#include "CoreMinimal.h"
#include "Lyz_DungeonBase.h"
#include "Lyz_DungeonCorner.generated.h"

UCLASS()
class PROJECT_LYZANDRED_API ALyz_DungeonCorner : public ALyz_DungeonBase
{
	GENERATED_BODY()

public:
	ALyz_DungeonCorner();

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void SetupMeshComponents() override;

public:
	UPROPERTY(EditAnywhere, Category="Meshes")
	UStaticMesh* CornerMesh = nullptr;

private:
	UPROPERTY()
	UInstancedStaticMeshComponent* Corners = nullptr;

	void GenerateDungeonWallMeshes(float TileSize, float BaseZ) const;

	void GenerateCornerMeshes(float TileSize, float CornerSize, float BaseZ) const;
};
