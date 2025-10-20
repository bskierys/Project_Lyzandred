#include "Lyz_DungeonTunnel.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Project_Lyzandred/Props/Lyz_MeshSizeLibrary.h"

ALyz_DungeonTunnel::ALyz_DungeonTunnel() : ALyz_DungeonBase()
{
}

void ALyz_DungeonTunnel::BeginPlay()
{
	Super::BeginPlay();
}

void ALyz_DungeonTunnel::GenerateWallMeshes(const float TileSize, const float BaseZ)
{
	for (int32 X = 0; X < LengthInSections; ++X)
	{
		for (int32 H = 0; H < HeightInSections; ++H)
		{
			const float Z = BaseZ + (H * TileSize);

			// Left wall
			const bool bSkipLeft = LeftWallGaps.Contains(H)
				&& LeftWallGaps[H].SkipXIndices.Contains(X);

			if (!bSkipLeft)
			{
				FVector LeftLoc(X * TileSize, -TileSize / 2.f, Z);
				FRotator LeftRot = FRotator(0, 0, 0);
				Walls->AddInstance(FTransform(LeftRot, LeftLoc));
			}

			// Right wall
			const bool bSkipRight = RightWallGaps.Contains(H) &&
				RightWallGaps[H].SkipXIndices.Contains(X);

			if (!bSkipRight)
			{
				FVector RightLoc(X * TileSize, WidthInSections * TileSize - TileSize / 2.f, Z);
				FRotator RightRot = FRotator(0, 0, 0);
				Walls->AddInstance(FTransform(RightRot, RightLoc));
			}
		}
	}
}

void ALyz_DungeonTunnel::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	const float TileSize = ULyz_MeshSizeLibrary::GetDungeonWallSizeFromMesh(WallMesh, 400.f);
	const float BaseZ = ElevationInSections * TileSize;

	GenerateFloorMeshes(TileSize, BaseZ);
	GenerateWallMeshes(TileSize, BaseZ);
}
