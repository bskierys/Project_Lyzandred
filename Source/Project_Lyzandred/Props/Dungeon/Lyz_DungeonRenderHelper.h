#pragma once

#include "CoreMinimal.h"
#include "Lyz_DungeonRenderHelper.generated.h"

class UStaticMesh;

/**
 * Describes a rectangular gap to carve out of the wall.
 * - Start: tile index along X where the opening begins
 * - Width: number of tiles along X for the opening
 * - BottomRow: starting row (Z) to carve from (0 = ground row)
 * - Height: number of rows to remove
 */
USTRUCT(BlueprintType)
struct FLyz_DungeonGap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gaps", meta=(ClampMin="0"))
	int32 ColStart = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gaps", meta=(ClampMin="1"))
	int32 Width = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gaps", meta=(ClampMin="0"))
	int32 RowStart = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gaps", meta=(ClampMin="1"))
	int32 Height = 1;

	bool Contains(int32 X, int32 Row) const
	{
		return (X >= ColStart && X < ColStart + Width) && (Row >= RowStart && Row < RowStart + Height);
	}
};

/**
 * Utility functions for dungeon tunnel generation
 */
UCLASS()
class PROJECT_LYZANDRED_API ULyz_DungeonRenderHelper: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * Calculate the tile size from a static mesh's bounds
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Meshes")
	static float GetMeshSizeX(const UStaticMesh* Mesh, const float DefaultSize = 400.f);

	UFUNCTION(BlueprintCallable, Category="Meshes")
	static TArray<FTransform> GenerateWallTransforms(int32 BaseLayers, float TileSize, TArray<FLyz_DungeonGap> Gaps, int32 Length, int32 Height);

	UFUNCTION(BlueprintCallable, Category="Meshes")
	static TArray<FTransform> GenerateFloorTransforms(int32 BaseLayers, float TileSize, TArray<FLyz_DungeonGap> Gaps, int32 Length, int32 Width);

	UFUNCTION(BlueprintCallable, Category="Meshes")
	static TArray<FTransform> GenerateBaseTransforms(int32 BaseLayers, float TileSize, TArray<FLyz_DungeonGap> Gaps, int32 Length, int32 Width);

private:
	static bool IsGapped(TArray<FLyz_DungeonGap> Gaps, int32 X, int32 Y);
};
