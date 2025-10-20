#include "Lyz_RectangleCoinSpawnerBase.h"


ALyz_RectangleCoinSpawnerBase::ALyz_RectangleCoinSpawnerBase()
{
}

void ALyz_RectangleCoinSpawnerBase::BeginPlay()
{
	Super::BeginPlay();
}

ALyz_CoinPickup* ALyz_RectangleCoinSpawnerBase::SpawnSingleCoin(const int32 Index,
	TSubclassOf<ALyz_CoinPickup> CoinClass)
{
	const int32 Row = Index / Columns;
	const int32 Column = Index % Columns;

	const FTransform BaseTransform = GetActorTransform();

	FVector Location = BaseTransform.GetLocation();
	FVector NormalizedDirection = Direction.IsNearlyZero() ? FVector(1.0f, 0.0f, 0.0f) : Direction.GetSafeNormal();
	NormalizedDirection.Normalize();
	
	auto CoinOffset = NormalizedDirection * Row * Gap;
	CoinOffset.X += Column * Gap;
	Location += CoinOffset;

	FTransform CoinTransform = BaseTransform;
	CoinTransform.SetLocation(Location);

	return SpawnCoinActorAtLocation(CoinTransform, CoinClass);
}
