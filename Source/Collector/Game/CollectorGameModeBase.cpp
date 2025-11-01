// Copyrights Plejady Team


#include "CollectorGameModeBase.h"

FCardData* ACollectorGameModeBase::GetCardDataByTag(const FGameplayTag& Tag) const
{
	return GetDataTableRowByTag<FCardData>(CardDataTable, Tag);
}

FSpecialMoveData* ACollectorGameModeBase::GetSpecialMoveDataByTag(const FGameplayTag& Tag) const
{
	return GetDataTableRowByTag<FSpecialMoveData>(SpecialMoveDataTable, Tag);
}
