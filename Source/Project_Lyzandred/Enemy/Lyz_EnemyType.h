#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Lyz_EnemyType.generated.h"

UCLASS(Blueprintable)
class PROJECT_LYZANDRED_API ULyz_EnemyType : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FName TypeId = FName(NAME_None);
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText Description = FText::FromString("Enemy");
};
