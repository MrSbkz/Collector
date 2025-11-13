// Copyrights Plejady Team

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DeckComponent.generated.h"

struct FCardDetails;
class ACardActor;
struct FGameplayTag;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COLLECTOR_API UDeckComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDeckComponent();
	void SpawnCards(const FTransform& CardsTransform);
	void SetHighlightedCard(AActor* Actor);
	AActor* SelectNextCard(int32 Value);

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> StartupCardsTags;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACardActor> CardClass;

	UPROPERTY(EditDefaultsOnly)
	int32 InitialHandCardsNum = 3;

	UPROPERTY(EditDefaultsOnly)
	float CardSpacing = 200.0f;

	UPROPERTY(EditDefaultsOnly)
	float RotationStep = 5.0f;

	UPROPERTY(EditDefaultsOnly)
	float OffsetZCoefficient = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	bool IsFanSpawning = false;

private:
	void LoadCards();
	void InitializeCardsInHand(const FTransform& CardsTransform);
	void UpdateHandLayout(const FTransform& CardsTransform);
	int32 GetHighlightedCardIndex() const;
	
	UPROPERTY()
	TArray<ACardActor*> HandCards;

	UPROPERTY()
	TArray<FCardDetails> PlayerCards;

	UPROPERTY()
	TArray<FCardDetails> RemainingCards;

	UPROPERTY()
	TObjectPtr<AActor> HighlightedActor;
};
