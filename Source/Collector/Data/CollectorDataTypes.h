#pragma once
#include "GameplayTagContainer.h"
#include "CollectorDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FCardData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag CardTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString CardName = FString();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> CardFaceImage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Capacity = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 AttackValue = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 AttackValueAttachCost = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 HealthValue = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 HealthValueAttachCost = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag SpecialMoveTag = FGameplayTag();
};

USTRUCT(BlueprintType)
struct FSpecialMoveData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag SpecialMoveTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Description = FString();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 SpecialMoveAttachCost = 0;
};