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

	PickedCardBillboardComponent = CreateDefaultSubobject<UBillboardComponent>("PickedCardBillboardComponent");
	PickedCardBillboardComponent->SetupAttachment(CameraComponent);
}

void ACollectorBattlePawn::BeginPlay()
{
	Super::BeginPlay();

	DeckComponent->SpawnCards(CardsBillboardComponent->GetComponentTransform());
}

FVector ACollectorBattlePawn::GetPickedCardLocation_Implementation()
{
	return PickedCardBillboardComponent->GetComponentLocation();
}
