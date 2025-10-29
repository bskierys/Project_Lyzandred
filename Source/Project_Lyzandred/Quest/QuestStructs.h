#pragma once

#include "CoreMinimal.h"
#include "QuestStructs.generated.h"

USTRUCT(BlueprintType)
struct FQuestDescription
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quest")
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quest")
	FText Description;
};

UENUM(BlueprintType)
enum class EQuestState : uint8
{
	Inactive = 0 UMETA(DisplayName = "Inactive"),
	Active = 1 UMETA(DisplayName = "Active"),
	Completed = 2 UMETA(DisplayName = "Completed"),
};
