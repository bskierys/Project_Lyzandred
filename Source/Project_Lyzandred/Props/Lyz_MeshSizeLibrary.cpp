#include "Lyz_MeshSizeLibrary.h"
#include "Engine/StaticMesh.h"

float ULyz_MeshSizeLibrary::GetDungeonWallSizeFromMesh(const UStaticMesh* Mesh, const float DefaultSize)
{
	if (Mesh)
	{
		const FBoxSphereBounds Bounds = Mesh->GetBounds();
		return Bounds.BoxExtent.X * 2.0f;
	}
	return DefaultSize;
}
