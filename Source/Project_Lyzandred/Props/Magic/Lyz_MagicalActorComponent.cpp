#include "Lyz_MagicalActorComponent.h"

#include "Project_Lyzandred/Game/Lyz_GameStateLibrary.h"

ULyz_MagicalActorComponent::ULyz_MagicalActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULyz_MagicalActorComponent::BeginPlay()
{
	Super::BeginPlay();

	GameStateRef = ULyz_GameStateLibrary::GetLyzGameState();
	if (IsValid(GameStateRef))
	{
		GameStateRef->OnKeyChanged.AddDynamic(this, &ULyz_MagicalActorComponent::HandleOnKeyChanged);
	}

	if (MagicFormAsset)
	{
		bIsInMagicForm = ULyz_GameStateLibrary::IsCharacterInForm(MagicFormAsset, GameStateRef->KeyValues);
	}

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	Owner->Tags.Add("Magic");

	TArray<UPrimitiveComponent*> Prims;
	Owner->GetComponents<UPrimitiveComponent>(Prims);

	for (UPrimitiveComponent* Prim : Prims)
	{
		FPrimitiveComponentInfo Info;
		Info.Component = Prim;
		Info.Responses = Prim->GetCollisionResponseToChannels();
		Info.CollisionEnabled = Prim->GetCollisionEnabled();
		Info.OriginalMaterial = Prim->GetMaterial(0);
		Info.bCastShadow = Prim->CastShadow;
		Info.bGeneratesOverlapEvents = Prim->GetGenerateOverlapEvents();
		PrimitiveComponents.Add(Info);
	}

	GlowingOverlay = UMaterialInstanceDynamic::Create(MagicalOverlayMaterial, this);
	GlowingOverlay->SetScalarParameterValue("GlowIntensity", 0.f);
	GlowingOverlay->SetScalarParameterValue("Exponent", 0.5f);

	for (FPrimitiveComponentInfo Info : PrimitiveComponents)
	{
		if (TWeakObjectPtr<UPrimitiveComponent> Prim = Info.Component; Prim->IsA<UStaticMeshComponent>())
		{
			UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Prim.Get());
			StaticMesh->SetOverlayMaterial(GlowingOverlay);
			// Nanite does not work with Overlay Material. Force Disable it.
			StaticMesh->SetForceDisableNanite(true);
		}
	}
}

void ULyz_MagicalActorComponent::HandleOnKeyChanged(FName Key, bool bValue)
{
	if (!MagicFormAsset || !GameStateRef)
	{
		return;
	}

	if (ULyz_GameStateLibrary::IsCharacterInForm(MagicFormAsset, GameStateRef->KeyValues))
	{
		if (!bIsInMagicForm)
		{
			OnToMagicForm();
		}
	}
	else
	{
		if (bIsInMagicForm)
		{
			OnFromMagicForm();
		}
	}
}

void ULyz_MagicalActorComponent::OnToMagicForm_Implementation()
{
	bIsInMagicForm = true;
	GlowingOverlay->SetScalarParameterValue("GlowIntensity", GlowIntensity);
}

void ULyz_MagicalActorComponent::OnFromMagicForm_Implementation()
{
	bIsInMagicForm = false;
	GlowingOverlay->SetScalarParameterValue("GlowIntensity", 0.f);
}


