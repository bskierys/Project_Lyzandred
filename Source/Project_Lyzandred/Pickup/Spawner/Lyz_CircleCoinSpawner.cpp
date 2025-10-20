#include "Lyz_CircleCoinSpawner.h"

ALyz_CircleCoinSpawner::ALyz_CircleCoinSpawner()
{
}

void ALyz_CircleCoinSpawner::BeginPlay()
{
	Super::BeginPlay();
}

ALyz_CoinPickup* ALyz_CircleCoinSpawner::SpawnSingleCoin(const int32 Index, TSubclassOf<ALyz_CoinPickup> CoinClass)
{
	const int32 TotalNumberOfCoins = CoinTypesToSpawn.Num();
	const float Degrees = Index * 360.f / static_cast<float>(TotalNumberOfCoins);
	const float Radians = FMath::DegreesToRadians(Degrees);

	const auto XLocationOffset = CoinSpawnRadius * FMath::Cos(Radians);
	const auto YLocationOffset = CoinSpawnRadius * FMath::Sin(Radians);
	const FTransform BaseTransform = GetActorTransform();

	FVector Location = BaseTransform.GetLocation();
	Location.X += XLocationOffset;
	Location.Y += YLocationOffset;

	FTransform CoinTransform = BaseTransform;
	CoinTransform.SetLocation(Location);

	return SpawnCoinActorAtLocation(CoinTransform, CoinClass);
}
