#include "Lyz_BlinkComponent.h"
#include "Project_Lyzandred/Lyz_WorldLibrary.h"

ULyz_BlinkComponent::ULyz_BlinkComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULyz_BlinkComponent::StartBlink(float DelayBeforeFirstBlink, float TimeBetweenBlinks, int32 NumberOfBlinks)
{
	// Reset
	InDelayBeforeFirstBlink = DelayBeforeFirstBlink;
	InTimeBetweenBlinks = TimeBetweenBlinks;
	InNumberOfBlinks = NumberOfBlinks;

	const UWorld* World = ULyz_WorldLibrary::GetWorldSafe();
	if (World)
	{
		World->GetTimerManager().ClearTimer(BlinkTimerHandle);
	}

	BlinkCount = 0;
	bIsBlinking = true;

	if (UMeshComponent* Mesh = GetMeshComponent())
	{
		Mesh->SetVisibility(true, true);
	}

	// Start timer
	if (World)
	{
		World->GetTimerManager().SetTimer(
			BlinkTimerHandle,
			this,
			&ULyz_BlinkComponent::HandleBlink,
			InTimeBetweenBlinks,
			true,
			InDelayBeforeFirstBlink
		);
	}
}

void ULyz_BlinkComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULyz_BlinkComponent::HandleBlink()
{
	BlinkCount++;

	const UWorld* World = ULyz_WorldLibrary::GetWorldSafe();
	if (!IsValid(World))
	{
		return;
	}

	if (UMeshComponent* Mesh = GetMeshComponent())
	{
		Mesh->SetVisibility(!Mesh->IsVisible(), true);
	}

	if (BlinkCount >= InNumberOfBlinks * 2) // *2 = on/off cycles
	{
		if (World)
		{
			World->GetTimerManager().ClearTimer(BlinkTimerHandle);
		}

		if (UMeshComponent* Mesh = GetMeshComponent())
		{
			Mesh->SetVisibility(true, true);
		}

		bIsBlinking = false;
	}
}

UMeshComponent* ULyz_BlinkComponent::GetMeshComponent() const
{
	if (const AActor* Owner = GetOwner())
	{
		return Owner->FindComponentByClass<UMeshComponent>();
	}
	return nullptr;
}

