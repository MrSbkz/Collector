// Copyrights Plejady Team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CollectorBattlePlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class COLLECTOR_API ACollectorBattlePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> SwitchCameraAction;

private:
	void SwitchCamera();
};
