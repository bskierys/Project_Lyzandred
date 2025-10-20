#pragma once

#include "CoreMinimal.h"
#include "Lyz_RectangleCoinSpawnerBase.h"
#include "Lyz_RectangleCoinSpawner.generated.h"

UCLASS()
class PROJECT_LYZANDRED_API ALyz_RectangleCoinSpawner : public ALyz_RectangleCoinSpawnerBase
{
	GENERATED_BODY()

public:
	ALyz_RectangleCoinSpawner(); 

protected:
	virtual void BeginPlay() override;
};
