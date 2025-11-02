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
	void SpawnCards();

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
	FTransform HandCardsTransform;

	UPROPERTY(EditDefaultsOnly)
	float OffsetZCoefficient = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	bool IsFanSpawning = false;

private:
	void LoadCards();
	void InitializeCardsInHand();
	void UpdateHandLayout();
	
	UPROPERTY()
	TArray<ACardActor*> HandCards;

	UPROPERTY()
	TArray<FCardDetails> PlayerCards;

	UPROPERTY()
	TArray<FCardDetails> RemainingCards;
};
