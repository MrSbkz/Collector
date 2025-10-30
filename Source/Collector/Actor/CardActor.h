// Copyrights Plejady Team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardActor.generated.h"

USTRUCT(BlueprintType)
struct FCardDetails
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString CardName = FString();

	UPROPERTY(BlueprintReadOnly)
	FString SpecialName = FString();

	UPROPERTY(BlueprintReadOnly)
	FString SpecialDescription = FString();

	UPROPERTY(BlueprintReadOnly)
	int32 CardCapacity = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 SpecialCapacity = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 AttackCapacity = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 AttackValue = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 HealthCapacity = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 HealthValue = 0;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTexture2D> CardFaceImage = nullptr;
};

UCLASS()
class COLLECTOR_API ACardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACardActor();

};
