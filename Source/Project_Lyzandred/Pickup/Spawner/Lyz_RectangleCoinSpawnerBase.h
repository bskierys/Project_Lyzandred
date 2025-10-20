#pragma once

#include "CoreMinimal.h"
#include "Lyz_CoinSpawner.h"
#include "Lyz_RectangleCoinSpawnerBase.generated.h"

UCLASS(Abstract)
class PROJECT_LYZANDRED_API ALyz_RectangleCoinSpawnerBase : public ALyz_CoinSpawner
{
	GENERATED_BODY()

public:
	ALyz_RectangleCoinSpawnerBase();

protected:
	virtual void BeginPlay() override;

	// custom
	virtual ALyz_CoinPickup* SpawnSingleCoin(const int32 Index, TSubclassOf<ALyz_CoinPickup> CoinClass) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arrangement", meta=(ClampMin="1", MakeEditWidget = true))
	FVector Direction = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arrangement|Grid", meta=(ClampMin="1"))
	int32 Rows = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arrangement|Grid", meta=(ClampMin="1"))
	int32 Columns = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arrangement", meta=(ClampMin="1"))
	float Gap = 150.f;
};
