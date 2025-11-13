// Copyrights Plejady Team

#include "DeckComponent.h"
#include "Collector/CollectorLogChannels.h"
#include "Collector/Actor/CardActor.h"
#include "Collector/Game/CollectorGameModeBase.h"
#include "Kismet/GameplayStatics.h"

UDeckComponent::UDeckComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDeckComponent::SpawnCards(const FTransform& CardsTransform)
{
	LoadCards();
	InitializeCardsInHand(CardsTransform);
	UpdateHandLayout(CardsTransform);
}

void UDeckComponent::SetHighlightedCard(AActor* Actor)
{
	HighlightedActor = Actor;
}

AActor* UDeckComponent::SelectNextCard(const int32 Value)
{
	if (HandCards.Num() == 0) return nullptr;

	if (!HighlightedActor)
	{
		return HandCards[0];
	}

	const int32 HighlightedActorIndex = GetHighlightedCardIndex();
	const int32 NextIndex = HighlightedActorIndex + Value;
	if (NextIndex < 0 || NextIndex >= HandCards.Num())
	{
		return HighlightedActor;
	}

	return HandCards[NextIndex];
}

void UDeckComponent::LoadCards()
{
	// I think I'll need to load Player Cards from disk first, and then check if we don't have any loaded data
	// that means that's the first battle and we need to create cards data using StartupCardTags 
	if (PlayerCards.Num() > 0) return;

	const ACollectorGameModeBase* GameMode = Cast<ACollectorGameModeBase>(UGameplayStatics::GetGameMode(GetOwner()));
	int32 CardId = 1;
	for (const FGameplayTag& CardTag : StartupCardsTags)
	{
		if (FCardData* CardData = GameMode->GetCardDataByTag(CardTag))
		{
			FCardDetails CardDetails;
			CardDetails.CardId = CardId;
			CardDetails.CardTag = CardTag;
			CardDetails.AttackCost = CardData->AttackValueAttachCost;
			CardDetails.AttackValue = CardData->AttackValue;
			CardDetails.CardCapacity = CardData->Capacity;
			CardDetails.CardFaceImage = CardData->CardFaceImage;
			CardDetails.CardName = CardData->CardName;
			CardDetails.HealthCost = CardData->HealthValueAttachCost;
			CardDetails.HealthValue = CardData->HealthValue;

			if (FSpecialMoveData* SpecialMoveData = GameMode->GetSpecialMoveDataByTag(CardData->SpecialMoveTag))
			{
				CardDetails.SpecialCost = SpecialMoveData->SpecialMoveAttachCost;
				CardDetails.SpecialName = SpecialMoveData->Name;
				CardDetails.SpecialDescription = SpecialMoveData->Description;
			}

			PlayerCards.Add(CardDetails);
			CardId++;
		}
		else
		{
			UE_LOG(LogCollector, Error, TEXT("Failed to get Gard Data by Tag: [%s]"), *CardTag.ToString());
		}
	}
}

void UDeckComponent::InitializeCardsInHand(const FTransform& CardsTransform)
{
	const int32 CardsNumToSpawn = InitialHandCardsNum > PlayerCards.Num() ? PlayerCards.Num() : InitialHandCardsNum;

	for (int i = 0; i < CardsNumToSpawn; ++i)
	{
		const FCardDetails CardDetails = PlayerCards[FMath::RandRange(0, PlayerCards.Num() - 1)];
		ACardActor* Card = GetWorld()->SpawnActorDeferred<ACardActor>(
			CardClass,
			CardsTransform,
			GetOwner(),
			Cast<APawn>(GetOwner()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		HandCards.Add(Card);
		PlayerCards.Remove(CardDetails);

		Card->FinishSpawning(CardsTransform);
		Card->SetData(CardDetails);
	}

	RemainingCards = PlayerCards;
}

void UDeckComponent::UpdateHandLayout(const FTransform& CardsTransform)
{
	const int32 NumCards = HandCards.Num();
	if (NumCards == 0) return;

	const FVector Center = CardsTransform.GetLocation();
	const FRotator BaseRotation = CardsTransform.Rotator();

	for (int32 i = 0; i < NumCards; i++)
	{
		const float OffsetY = -((i - (NumCards - 1) / 2.0f) * CardSpacing);
		float Angle = 0.f;

		FVector TargetLocation = Center + HandCards[i]->GetActorRightVector() * OffsetY;

		if (IsFanSpawning)
		{
			TargetLocation.Z -= FMath::Abs(Angle) * OffsetZCoefficient;
			Angle = (i - (NumCards - 1) / 2.0f) * RotationStep;
		}

		const FRotator TargetRotation = BaseRotation + FRotator(0.f, 0.f, Angle);

		if (HandCards[i])
		{
			// TODO: I could make a smooth animation here(Timeline/InterpTo), it's just a teleport for now
			HandCards[i]->SetActorLocationAndRotation(TargetLocation, TargetRotation);
		}
	}
}

int32 UDeckComponent::GetHighlightedCardIndex() const
{
	if (!HighlightedActor) return 0;

	for (int i = 0; i < HandCards.Num(); ++i)
	{
		if (HandCards[i] == Cast<ACardActor>(HighlightedActor))
		{
			return i;
		}
	}

	return 0;
}
