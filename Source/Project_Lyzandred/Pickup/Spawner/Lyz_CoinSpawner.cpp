#include "Lyz_CoinSpawner.h"

ALyz_CoinSpawner::ALyz_CoinSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALyz_CoinSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnCoins();
	if (!bCoinsVisible)
	{
		HideCoins();
	}
}

void ALyz_CoinSpawner::SpawnCoins()
{
	if (!IsValid(CoinMapper))
	{
		UE_LOG(LogTemp, Error, TEXT("ALyz_CoinSpawner: CoinMapper not provided"));
		return;
	}

	SpawnedCoins.Empty();
	CoinTypesToSpawn.Empty();

	for (const auto Coin : Coins)
	{
		for (int32 Index = 0; Index < Coin.Value; ++Index)
		{
			CoinTypesToSpawn.Add(Coin.Key);
		}
	}

	const TArray<TSubclassOf<ALyz_CoinPickup>> CoinClasses = CoinMapper->GetCoinsToSpawn(CoinTypesToSpawn);
	TArray<ALyz_CoinPickup*> Spawned = SpawnCoinsToScene(CoinClasses);

	for (const auto SpawnedCoin : Spawned)
	{
		if (IsValid(SpawnedCoin))
		{
			SpawnedCoins.Add(SpawnedCoin);
		}
	}
}

TArray<ALyz_CoinPickup*> ALyz_CoinSpawner::SpawnCoinsToScene(const TArray<TSubclassOf<ALyz_CoinPickup>>& CoinClasses)
{
	TArray<ALyz_CoinPickup*> Spawned;

	for (int32 Index = 0; Index < CoinClasses.Num(); ++Index)
	{
		const auto CoinClass = CoinClasses[Index];
		if (!IsValid(CoinClass))
		{
			continue;
		}

		const auto SpawnedActor = SpawnSingleCoin(Index, CoinClass);
		if (IsValid(SpawnedActor))
		{
			Spawned.Add(SpawnedActor);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn actor %s"), *CoinClass->GetName());
		}
	}

	return Spawned;
}

ALyz_CoinPickup* ALyz_CoinSpawner::SpawnCoinActorAtLocation(const FTransform& Transform,
                                                            const TSubclassOf<ALyz_CoinPickup>& ActorClass)
{
	if (!GetWorld() || !ActorClass)
	{
		return nullptr;
	}

	FActorSpawnParameters SpawnInfo = FActorSpawnParameters();
	SpawnInfo.Owner = this;
	const auto Spawned = GetWorld()->SpawnActor<ALyz_CoinPickup>(ActorClass.Get(), Transform, SpawnInfo);

	if (!IsValid(Spawned))
	{
		return nullptr;
	}

	Spawned->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

	return Spawned;
}

void ALyz_CoinSpawner::HideCoins()
{
	for (const auto Coin : SpawnedCoins)
	{
		if (IsValid(Coin))
		{
			Coin->Hide();
		}
	}
	bCoinsVisible = false;
}

void ALyz_CoinSpawner::AnimateCoinSpawn()
{
	if (bCoinsVisible)
	{
		return;
	}

	for (int32 i = 0; i < SpawnedCoins.Num(); ++i)
	{
		const auto Coin = SpawnedCoins[i];
		if (!IsValid(Coin) || !Coin->IsA(ALyz_CoinPickup::StaticClass()))
		{
			continue;
		}
		Coin->AnimateCoinSpawn(i * DelayBetweenShowingCoins);
	}

	bCoinsVisible = true;
}

void ALyz_CoinSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
