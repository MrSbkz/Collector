// Copyrights Plejady Team

#pragma once

#include "CoreMinimal.h"
#include "Collector/Interface/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "CardSlotActor.generated.h"

UCLASS()
class COLLECTOR_API ACardSlotActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	ACardSlotActor();

	/** Interaction Interface */
	virtual void Highlight() override;
	virtual void Unhighlight() override;
	/** end Interaction Interface */

	bool IsEmpty() const { return IsSlotEmpty; }

private:
	bool IsSlotEmpty = false;
};
