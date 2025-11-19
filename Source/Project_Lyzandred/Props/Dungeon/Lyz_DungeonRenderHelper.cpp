#include "Lyz_DungeonRenderHelper.h"

#include "VectorTypes.h"
#include "Engine/StaticMesh.h"
#include "HLSLTree/HLSLTreeTypes.h"

float ULyz_DungeonRenderHelper::GetMeshSizeX(const UStaticMesh* Mesh, const float DefaultSize)
{
	if (Mesh)
	{
		const FBoxSphereBounds Bounds = Mesh->GetBounds();
		return Bounds.BoxExtent.X * 2.0f;
	}
	return DefaultSize;
}

TArray<FTransform> ULyz_DungeonRenderHelper::GenerateWallTransforms(
	const int32 BaseLayers, const float TileSize,
	const TArray<FLyz_DungeonGap> Gaps,
	const int32 Length, const int32 Height
)
{
	TArray<FTransform> Tiles;
	const float BaseZ = BaseLayers * TileSize;
	
	for (int32 H = 0; H < Height; ++H)
	{
		const float Z = BaseZ + (H * TileSize);

		for (int32 X = 0; X < Length; ++X)
		{
			if (IsGapped(Gaps, X, H))
			{
				continue;
			}

			const FVector Loc(X * TileSize, 0.f, Z);
			const FRotator Rot(0.f, 0.f, 0.f);
			Tiles.Add(FTransform(Rot, Loc));
		}
	}
	return Tiles;
}

TArray<FTransform> ULyz_DungeonRenderHelper::GenerateFloorTransforms(
	const int32 BaseLayers, const float TileSize,
	const TArray<FLyz_DungeonGap> Gaps,
	const int32 Length, const int32 Width
)
{
	TArray<FTransform> Tiles;
	const float BaseZ = BaseLayers * TileSize;

	for (int32 X = 0; X < Length; ++X)
	{
		for (int32 Y = 0; Y < Width; ++Y)
		{
			if (IsGapped(Gaps, X, Y))
			{
				continue;
			}

			const FVector Loc(X * TileSize, Y * TileSize, BaseZ);
			const FRotator Rot(0.f, 0.f, 0.f);
			Tiles.Add(FTransform(Rot, Loc));
		}
	}

	return Tiles;
}

TArray<FTransform> ULyz_DungeonRenderHelper::GenerateBaseTransforms(
	const int32 BaseLayers, const float TileSize,
	const TArray<FLyz_DungeonGap> Gaps,
	const int32 Length, const int32 Width
)
{
	TArray<FTransform> Tiles;
	for (int32 X = 0; X < Length; ++X)
	{
		for (int32 Y = 0; Y < Width; ++Y)
		{
			if (IsGapped(Gaps, X, Y))
			{
				continue;
			}

			for (int32 Layer = 0; Layer < BaseLayers; ++Layer)
			{
				const FVector Loc(X * TileSize, Y * TileSize, Layer * TileSize);
				const FRotator Rot(0.f, 0.f, 0.f);
				Tiles.Add(FTransform(Rot, Loc));
			}
		}
	}
	return Tiles;
}

bool ULyz_DungeonRenderHelper::IsGapped(TArray<FLyz_DungeonGap> Gaps, int32 X, int32 Y)
{
	for (const FLyz_DungeonGap& Gap : Gaps)
	{
		if (Gap.Contains(X, Y))
		{
			return true;
		}
	}
	return false;
}
