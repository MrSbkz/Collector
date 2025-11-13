// Copyrights Plejady Team

#include "CardActor.h"

ACardActor::ACardActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACardActor::Highlight()
{
	if (IsPicked) return;
	
	if (AActor* OwnerActor = GetOwner())
	{
		if (const APawn* OwnerPawn = Cast<APawn>(OwnerActor))
		{
			if (const APlayerController* PC = Cast<APlayerController>(OwnerPawn->GetController()))
			{
				InitialLocation = GetActorLocation();
				int32 ViewportX, ViewportY;
				PC->GetViewportSize(ViewportX, ViewportY);
				const float ScreenX = ViewportX / 2.0f;
				const float ScreenY = ViewportY / 2.0f;

				FVector WorldLocation;
				FVector WorldDirection;

				if (!PC->DeprojectScreenPositionToWorld(ScreenX, ScreenY, WorldLocation, WorldDirection))
					return;

				FVector CamLocation;
				FRotator CamRotation;
				PC->GetPlayerViewPoint(CamLocation, CamRotation);

				FVector TargetLocation = CamLocation + WorldDirection * HighlightingDistance;
				TargetLocation += CamRotation.Quaternion().GetUpVector() * HeightOffset;

				const FVector CurrentLocation = GetActorLocation();
				const FVector NewLocation = FMath::VInterpTo(
					CurrentLocation,
					TargetLocation,
					GetWorld()->GetDeltaSeconds(),
					HighlightingDistance);

				SetActorLocation(NewLocation);

				HighlightLocation = GetActorLocation();
				IsHighlighted = true;
			}
		}
	}
}

void ACardActor::Unhighlight()
{
	if (IsPicked) return;

	SetActorLocation(InitialLocation);
	IsHighlighted = false;
}

void ACardActor::SetData(const FCardDetails& CardData)
{
	SetCardUI(CardData);
	CardDetails = CardData;
}
