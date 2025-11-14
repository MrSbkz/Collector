// Copyrights Plejady Team

#pragma once

#include "CoreMinimal.h"
#include "Collector/CollectorTypes.h"
#include "Collector/Interface/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "CardActor.generated.h"


UCLASS()
class COLLECTOR_API ACardActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	ACardActor();

	/** Interaction Interface */
	virtual void Highlight() override;
	virtual void Unhighlight() override;
	/** end Interaction Interface */

	void SetData(const FCardDetails& CardData);

	UFUNCTION(BlueprintImplementableEvent)
	void SetCardUI(const FCardDetails& CardData);

	UFUNCTION(BlueprintImplementableEvent)
	void MoveToLocation(const FVector& Location);

protected:
	UPROPERTY(EditDefaultsOnly, Category="Highlighting")
	float HighlightingDistance = 10.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Highlighting")
	float HeightOffset = 10.f;

	UPROPERTY(BlueprintReadOnly)
	FVector HighlightLocation = FVector();

	UPROPERTY(BlueprintReadOnly)
	FVector InitialLocation = FVector();

	UPROPERTY(BlueprintReadWrite)
	bool IsPicked = false;

private:
	FCardDetails CardDetails;
	bool IsHighlighted = false;
};
