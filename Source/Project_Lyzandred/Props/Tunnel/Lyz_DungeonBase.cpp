#include "Lyz_DungeonBase.h"
#include "Components/InstancedStaticMeshComponent.h"

ALyz_DungeonBase::ALyz_DungeonBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Floors = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Floors");
	Walls = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Walls");
	Supports = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Supports");

	RootComponent = Floors;
	Walls->SetupAttachment(RootComponent);
	Supports->SetupAttachment(RootComponent);
}

void ALyz_DungeonBase::BeginPlay()
{
	Super::BeginPlay();
}

void ALyz_DungeonBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetupMeshComponents();
}

void ALyz_DungeonBase::SetupMeshComponents()
{
	Floors->ClearInstances();
	Walls->ClearInstances();
	Supports->ClearInstances();

	if (FloorMesh) Floors->SetStaticMesh(FloorMesh);
	if (WallMesh) Walls->SetStaticMesh(WallMesh);
	if (SupportMesh) Supports->SetStaticMesh(SupportMesh);
}

void ALyz_DungeonBase::GenerateFloorMeshes(float TileSize, float BaseZ) const
{
	for (int32 X = 0; X < LengthInSections; ++X)
	{
		for (int32 Y = 0; Y < WidthInSections; ++Y)
		{
			FVector Loc(X * TileSize, Y * TileSize, BaseZ);
			Floors->AddInstance(FTransform(Loc));

			// Supports below (only if Elevation > 0)
			for (int32 E = 0; E < ElevationInSections; ++E)
			{
				FVector SupportLoc(X * TileSize, Y * TileSize, E * TileSize);
				Supports->AddInstance(FTransform(SupportLoc));
			}
		}
	}
}

void ALyz_DungeonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
