// Copyrights Plejady Team

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Collector/Interface/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "CardActor.generated.h"

USTRUCT(BlueprintType)
struct FCardDetails
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 CardId = 0;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag CardTag = FGameplayTag();

	UPROPERTY(BlueprintReadOnly)
	FString CardName = FString();

	UPROPERTY(BlueprintReadOnly)
	FString SpecialName = FString();

	UPROPERTY(BlueprintReadOnly)
	FString SpecialDescription = FString();

	UPROPERTY(BlueprintReadOnly)
	int32 CardCapacity = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 SpecialCost = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 AttackCost = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 AttackValue = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 HealthCost = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 HealthValue = 0;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTexture2D> CardFaceImage = nullptr;
};

inline bool operator==(const FCardDetails& Left, const FCardDetails& Right)
{
	return Left.CardId == Right.CardId;
}

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

protected:
	UPROPERTY(EditDefaultsOnly, Category="Highlighting")
	float HighlightingDistance = 10.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Highlighting")
	float HeightOffset = 10.f;

private:
	FCardDetails CardDetails;

	FTransform InitialTransform;
};
