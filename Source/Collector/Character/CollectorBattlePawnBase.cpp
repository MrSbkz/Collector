// Copyrights Plejady Team


#include "CollectorBattlePawnBase.h"
#include "Collector/Components/DeckComponent.h"

ACollectorBattlePawnBase::ACollectorBattlePawnBase()
{
	PrimaryActorTick.bCanEverTick = false;

	DeckComponent = CreateDefaultSubobject<UDeckComponent>("DeckComponent");
}

