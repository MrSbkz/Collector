// Copyrights Plejady Team


#include "CollectorBattlePawn.h"
#include "Collector/Components/DeckComponent.h"

ACollectorBattlePawn::ACollectorBattlePawn()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACollectorBattlePawn::BeginPlay()
{
	Super::BeginPlay();

	DeckComponent->SpawnCards();
}
