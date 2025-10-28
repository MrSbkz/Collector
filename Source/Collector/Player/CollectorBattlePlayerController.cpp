// Copyrights Plejady Team


#include "CollectorBattlePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Collector/Interface/PlayerInterface.h"

void ACollectorBattlePlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void ACollectorBattlePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(
			SwitchCameraAction,
			ETriggerEvent::Started,
			this,
			&ACollectorBattlePlayerController::SwitchCamera);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ACollectorBattlePlayerController::SwitchCamera()
{
	if (const IPlayerInterface* PlayerInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerInterface->Execute_SwitchCamera(GetPawn());
	}
}
