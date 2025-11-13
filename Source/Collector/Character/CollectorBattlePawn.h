// Copyrights Plejady Team

#pragma once

#include "CoreMinimal.h"
#include "CollectorBattlePawnBase.h"
#include "Collector/Interface/PlayerInterface.h"
#include "CollectorBattlePawn.generated.h"

class UCameraComponent;

UCLASS()
class COLLECTOR_API ACollectorBattlePawn : public ACollectorBattlePawnBase, public IPlayerInterface
{
	GENERATED_BODY()

public:
	ACollectorBattlePawn();

protected:
	virtual void BeginPlay() override;

	/** Player Interface*/
	virtual FVector GetPickedCardLocation_Implementation() override;
	/** end Player Interface*/

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBillboardComponent> CardsBillboardComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBillboardComponent> PickedCardBillboardComponent;
};
