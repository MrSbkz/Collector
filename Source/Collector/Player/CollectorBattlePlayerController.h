// Copyrights Plejady Team

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
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

public:
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SwitchCameraAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SelectRightActorAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SelectLeftActorAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> BaseSelectAction;

	UPROPERTY(
		EditDefaultsOnly,
		Category = "Input",
		meta = (ToolTip = "Mouse movement distance threshold to show cursor when using keyboard/gamepad input"))
	float MouseMovementThreshold = 5.f;

private:
	void CursorTrace();

	/** Input */
	void SwitchCamera();
	void OnSelectRightActor();
	void OnSelectLeftActor();
	void OnBaseSelect(const FInputActionValue& InputActionValue);
	/** end Input */

	void OnInputKeyPressed(const FKeyEvent& KeyEvent);
	void OnMouseKeyPressed(const FPointerEvent&);
	void UpdateActorHighlighting(AActor* Actor);
	void HandleMouseMovement();

	UPROPERTY()
	TObjectPtr<AActor> LastActor;

	UPROPERTY()
	TObjectPtr<AActor> ThisActor;

	FVector2D LastMousePos;
};
