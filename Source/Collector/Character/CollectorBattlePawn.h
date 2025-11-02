// Copyrights Plejady Team

#pragma once

#include "CoreMinimal.h"
#include "CollectorBattlePawnBase.h"
#include "Collector/Interface/PlayerInterface.h"
#include "CollectorBattlePawn.generated.h"

UCLASS()
class COLLECTOR_API ACollectorBattlePawn : public ACollectorBattlePawnBase, public IPlayerInterface
{
	GENERATED_BODY()

public:
	ACollectorBattlePawn();

protected:
	virtual void BeginPlay() override;
};
