#include "Lyz_DungeonWall.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Project_Lyzandred/Props/Lyz_MeshSizeLibrary.h"

ALyz_DungeonWall::ALyz_DungeonWall()
{
	PrimaryActorTick.bCanEverTick = false;

	Walls = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Walls");

	RootComponent = Walls;
}

void ALyz_DungeonWall::BeginPlay()
{
	Super::BeginPlay();
}

void ALyz_DungeonWall::GenerateWallMeshes(const float TileSize) const
{
	for (int32 H = 0; H < WallHeight; ++H)
	{
		const float Z = (H * TileSize);

		for (int32 X = 0; X < WallLength; ++X)
		{
			FVector WallLoc(X * TileSize, 0, Z);
			FRotator WallRot(0, 0, 0);
			Walls->AddInstance(FTransform(WallRot, WallLoc));
		}
	}
}

void ALyz_DungeonWall::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetupMeshComponents();

	const float TileSize = ULyz_MeshSizeLibrary::GetDungeonWallSizeFromMesh(WallMesh, 400.f);

	GenerateWallMeshes(TileSize);
}

void ALyz_DungeonWall::SetupMeshComponents()
{
	Walls->ClearInstances();

	if (WallMesh) Walls->SetStaticMesh(WallMesh);
}

