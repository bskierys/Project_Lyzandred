#include "Lyz_MagicRevealComponent.h"

#include "Lyz_MagicalActorComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/PrimitiveComponent.h"

ULyz_MagicRevealComponent::ULyz_MagicRevealComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULyz_MagicRevealComponent::BeginPlay()
{
	Super::BeginPlay();

	for (const FPrimitiveComponentInfo Info : PrimitiveComponents)
	{
		const TWeakObjectPtr<UPrimitiveComponent> Prim = Info.Component;
		Prim->SetGenerateOverlapEvents(true);
	}

	RefreshRevealState(bIsSolid);
}

void ULyz_MagicRevealComponent::SetRevealed(bool bRevealed)
{
	// TODO: Optimise this operation once the mechanic is settled
	// Not optimal to refresh everything everytime, but easier when still changing logic
	RefreshRevealState(bRevealed);
	bIsSolid = bRevealed;
}

void ULyz_MagicRevealComponent::RefreshRevealState(bool bNewSolid)
{
	if (bIsInMagicForm)
	{
		if (bNewSolid)
		{
			// set solid
			SetCollisionSolid(true, true);
		}
		else
		{
			// set pass through
			SetCollisionSolid(false, true);
		}
	} else
	{
		// set pass through
		SetCollisionSolid(false, false);
	}
}

void ULyz_MagicRevealComponent::SetCollisionSolid(bool bSolid, bool bMagicVisible)
{
	for (FPrimitiveComponentInfo Info : PrimitiveComponents)
	{
		TWeakObjectPtr<UPrimitiveComponent> Prim = Info.Component;
		if (bSolid)
		{
			Prim->SetGenerateOverlapEvents(Info.bGeneratesOverlapEvents);
		}
		else
		{
			Prim->SetGenerateOverlapEvents(false);
		}
		
		if (Prim->IsA<UShapeComponent>())
		{
			// this is a shape collision object
			if (bSolid)
			{
				Prim->SetCollisionEnabled(Info.CollisionEnabled);
			}
			else
			{
				Prim->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
		}
		else
		{
			if (bSolid)
			{
				Prim->SetCollisionEnabled(Info.CollisionEnabled);
				Prim->SetCollisionResponseToChannels(Info.Responses);
				if (Info.OriginalMaterial) Prim->SetMaterial(0, Info.OriginalMaterial);
				Prim->CastShadow = Info.bCastShadow;
			}
			else
			{
				// for not solid meshes, always set transparent material and not shadow
				if (TransparentMaterial) Prim->SetMaterial(0, TransparentMaterial);
				Prim->CastShadow = false;

				// instanced static meshes need special treatment
				if (Prim->IsA<UInstancedStaticMeshComponent>())
				{
					UInstancedStaticMeshComponent* ISMC = Cast<UInstancedStaticMeshComponent>(Prim);
					ISMC->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
					ISMC->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
					ISMC->BodyInstance.SetResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
					ISMC->RecreatePhysicsState(); // <- important, forces update
				}
				else
				{
					Prim->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
					Prim->SetCollisionResponseToAllChannels(ECR_Ignore);
					Prim->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
				}
			}
		}
	}
}

void ULyz_MagicRevealComponent::ToggleWithMagic_Implementation()
{
	SetRevealed(!bIsSolid);
}

void ULyz_MagicRevealComponent::ActivateWithMagic_Implementation()
{
	SetRevealed(true);
}

void ULyz_MagicRevealComponent::DeactivateWithMagic_Implementation()
{
	SetRevealed(false);
}

void ULyz_MagicRevealComponent::OnToMagicForm_Implementation()
{
	Super::OnToMagicForm_Implementation();
	RefreshRevealState(bIsSolid);
}

void ULyz_MagicRevealComponent::OnFromMagicForm_Implementation()
{
	Super::OnFromMagicForm_Implementation();
	RefreshRevealState(bIsSolid);
}
