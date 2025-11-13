// Copyrights Plejady Team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CollectorBattlePawnBase.generated.h"

class UDeckComponent;

UCLASS()
class COLLECTOR_API ACollectorBattlePawnBase : public APawn
{
	GENERATED_BODY()

public:
	ACollectorBattlePawnBase();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UDeckComponent> DeckComponent;
};
