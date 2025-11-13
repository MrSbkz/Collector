// Copyrights Plejady Team


#include "CollectorBattlePawn.h"
#include "Camera/CameraComponent.h"
#include "Collector/Components/DeckComponent.h"
#include "Components/BillboardComponent.h"

ACollectorBattlePawn::ACollectorBattlePawn()
{
	PrimaryActorTick.bCanEverTick = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());

	CardsBillboardComponent = CreateDefaultSubobject<UBillboardComponent>("CardsBillboardComponent");
	CardsBillboardComponent->SetupAttachment(CameraComponent);
}

void ACollectorBattlePawn::BeginPlay()
{
	Super::BeginPlay();

	DeckComponent->SpawnCards(CardsBillboardComponent->GetComponentTransform());
}

FTransform ACollectorBattlePawn::GetPickedCardTransform_Implementation()
{
	return PickedCardTransform;
}

ECameraPosition ACollectorBattlePawn::GetNextCameraPosition(
	const ECameraPosition CurrentCameraPosition,
	int32 NextCameraPositionIndex)
{
	UEnum* EnumPtr = StaticEnum<ECameraPosition>();
	if (NextCameraPositionIndex >= 0 && NextCameraPositionIndex < EnumPtr->NumEnums())
	{
		const ECameraPosition NextCameraPosition = static_cast<ECameraPosition>(NextCameraPositionIndex);

		if (CameraPositionsToTransforms.Contains(NextCameraPosition))
		{
			return NextCameraPosition;
		}
	}

	return CurrentCameraPosition;
}
