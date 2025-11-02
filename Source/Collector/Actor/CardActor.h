// Copyrights Plejady Team

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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
class COLLECTOR_API ACardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACardActor();

	void SetData(const FCardDetails& CardData);

	UFUNCTION(BlueprintImplementableEvent)
	void SetCardUI(const FCardDetails& CardData);

private:
	FCardDetails CardDetails;

};
