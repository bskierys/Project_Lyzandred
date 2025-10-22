#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Lyz_DeveloperSettings.generated.h"

class USubsystemConfig;

/**
 * Configuration for subsystems in the project.
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Lyzandred Config"))
class PROJECT_LYZANDRED_API ULyz_DeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	virtual FName GetCategoryName() const override { return TEXT("Lyzandred Project"); }

	UPROPERTY(EditAnywhere, config, Category="Subsystem|Config")
	TArray<TSoftObjectPtr<USubsystemConfig>> SubsystemConfig;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Subsystem|Config")
	USubsystemConfig* GetSubsystemConfigByClass(TSubclassOf<USubsystemConfig> ParamClass) const;
};
