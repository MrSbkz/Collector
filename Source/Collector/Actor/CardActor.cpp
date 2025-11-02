// Copyrights Plejady Team


#include "CardActor.h"

ACardActor::ACardActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACardActor::SetData(const FCardDetails& CardData)
{
	SetCardUI(CardData);
	CardDetails = CardData;
}
