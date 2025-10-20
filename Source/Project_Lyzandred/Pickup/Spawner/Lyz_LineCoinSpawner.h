#pragma once

#include "CoreMinimal.h"
#include "Lyz_RectangleCoinSpawner.h"
#include "Lyz_LineCoinSpawner.generated.h"

UCLASS(meta=(HideCategories="Arrangement|Grid"))
class PROJECT_LYZANDRED_API ALyz_LineCoinSpawner : public ALyz_RectangleCoinSpawnerBase
{
	GENERATED_BODY()
public:
	ALyz_LineCoinSpawner();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;
};
