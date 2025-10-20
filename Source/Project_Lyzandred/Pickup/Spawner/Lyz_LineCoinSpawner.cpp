#include "Lyz_LineCoinSpawner.h"

ALyz_LineCoinSpawner::ALyz_LineCoinSpawner()
{
	Columns = 1;
}

void ALyz_LineCoinSpawner::OnConstruction(const FTransform& Transform)
{
	// protect against cashed values on levels
	Super::OnConstruction(Transform);
	Columns = 1;
}

void ALyz_LineCoinSpawner::BeginPlay()
{
	Super::BeginPlay();
}
