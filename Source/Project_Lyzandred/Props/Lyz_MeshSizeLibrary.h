#pragma once

#include "CoreMinimal.h"
#include "Lyz_MeshSizeLibrary.generated.h"

class UStaticMesh;

/**
 * Utility functions for dungeon tunnel generation
 */
UCLASS()
class PROJECT_LYZANDRED_API ULyz_MeshSizeLibrary: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * Calculate the tile size from a static mesh's bounds
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Meshes")
	static float GetDungeonWallSizeFromMesh(const UStaticMesh* Mesh, const float DefaultSize = 400.f);
};
