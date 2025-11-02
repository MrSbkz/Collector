// Copyrights Plejady Team

#include "CollectorBattlePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Collector/Interface/InteractionInterface.h"
#include "Collector/Interface/PlayerInterface.h"

void ACollectorBattlePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

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

void ACollectorBattlePlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	if (LastActor != ThisActor)
	{
		if (LastActor && LastActor->Implements<UInteractionInterface>()) Cast<IInteractionInterface>(LastActor)->Unhighlight();
		if (ThisActor && ThisActor->Implements<UInteractionInterface>()) Cast<IInteractionInterface>(ThisActor)->Highlight();
	}
}
