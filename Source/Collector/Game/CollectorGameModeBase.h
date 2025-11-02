// Copyrights Plejady Team

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Collector/Data/CollectorDataTypes.h"
#include "GameFramework/GameModeBase.h"
#include "CollectorGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class COLLECTOR_API ACollectorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	FCardData* GetCardDataByTag(const FGameplayTag& Tag) const;
	FSpecialMoveData* GetSpecialMoveDataByTag(const FGameplayTag& Tag) const;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> CardDataTable;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> SpecialMoveDataTable;

private:
	template<typename T>
	static T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
T* ACollectorGameModeBase::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""), false);
}
