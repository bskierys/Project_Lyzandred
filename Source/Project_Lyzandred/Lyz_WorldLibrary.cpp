#include "Lyz_WorldLibrary.h"

UWorld* ULyz_WorldLibrary::GetWorldSafe()
{
	const UEngine* Engine = GEngine;

	if (!IsValid(Engine))
	{
		return nullptr;
	}

	const UGameViewportClient* ViewportClient = Engine->GameViewport;

	if (!IsValid(ViewportClient))
	{
		return nullptr;
	}
	
	UWorld* World = ViewportClient->GetWorld();

	if (!IsValid(World))
	{
		return nullptr;
	}

	return World;
}
