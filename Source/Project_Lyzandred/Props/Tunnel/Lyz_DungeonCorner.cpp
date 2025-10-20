#include "Lyz_DungeonCorner.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Project_Lyzandred/Props/Lyz_MeshSizeLibrary.h"

ALyz_DungeonCorner::ALyz_DungeonCorner() : ALyz_DungeonBase()
{
	Corners = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Corners");
	Corners->SetupAttachment(RootComponent);
}

void ALyz_DungeonCorner::BeginPlay()
{
	Super::BeginPlay();
}

void ALyz_DungeonCorner::SetupMeshComponents()
{
	Super::SetupMeshComponents();
	
	Corners->ClearInstances();
	if (CornerMesh) Corners->SetStaticMesh(CornerMesh);
}

void ALyz_DungeonCorner::GenerateDungeonWallMeshes(const float TileSize, const float BaseZ) const
{
	for (int32 H = 0; H < HeightInSections; ++H)
	{
		const float Z = BaseZ + (H * TileSize);

		// Left side walls
		for (int32 X = 0; X < LengthInSections; ++X)
		{
			FVector LeftLoc(X * TileSize, -TileSize / 2.f, Z);
			FRotator LeftRot = FRotator(0, 0, 0);
			Walls->AddInstance(FTransform(LeftRot, LeftLoc));
		}

		// Front facing walls
		for (int32 Y = 0; Y < WidthInSections; ++Y)
		{
			FVector FrontLoc(TileSize / 2 + (LengthInSections - 1) * TileSize, Y * TileSize, Z);
			FRotator FrontRot = FRotator(0, 90, 0);
			Walls->AddInstance(FTransform(FrontRot, FrontLoc));
		}
	}
}

void ALyz_DungeonCorner::GenerateCornerMeshes(const float TileSize, const float CornerSize, const float BaseZ) const
{
	if (CornerMesh)
	{
		constexpr float CornerPadding = 5.f;
		
		const float CornerX = LengthInSections * TileSize - (CornerSize - CornerPadding);
		const float CornerY = -(CornerSize+CornerPadding);

		for (int32 H = 0; H < HeightInSections; ++H)
		{
			const float Z = BaseZ + (H * TileSize);
			const FVector CornerLoc(CornerX, CornerY, Z);
			const FRotator CornerRot(0.f, 0.f, 0.f);
			Corners->AddInstance(FTransform(CornerRot, CornerLoc));
		}
	}
}

void ALyz_DungeonCorner::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	const float TileSize = ULyz_MeshSizeLibrary::GetDungeonWallSizeFromMesh(WallMesh);
	const float CornerSize = TileSize / 2;
	const float BaseZ = ElevationInSections * TileSize;

	GenerateFloorMeshes(TileSize, BaseZ);
	GenerateDungeonWallMeshes(TileSize, BaseZ);
	GenerateCornerMeshes(TileSize, CornerSize, BaseZ);
}

