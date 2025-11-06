// Copyrights Plejady Team

#include "CollectorBattlePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Collector/Components/DeckComponent.h"
#include "Collector/Interface/InteractionInterface.h"
#include "Collector/Interface/PlayerInterface.h"

void ACollectorBattlePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	HandleMouseMovement();

	if (bShowMouseCursor)
	{
		CursorTrace();
	}
}

void ACollectorBattlePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());

	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().OnApplicationPreInputKeyDownListener()
		                        .AddUObject(this, &ACollectorBattlePlayerController::OnInputKeyPressed);

		FSlateApplication::Get().OnApplicationMousePreInputButtonDownListener()
		                        .AddUObject(this, &ACollectorBattlePlayerController::OnMouseKeyPressed);
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
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
			NextCameraAction,
			ETriggerEvent::Started,
			this,
			&ACollectorBattlePlayerController::NextCamera);
		
		EnhancedInputComponent->BindAction(
			PreviousCameraAction,
			ETriggerEvent::Started,
			this,
			&ACollectorBattlePlayerController::PreviousCamera);

		EnhancedInputComponent->BindAction(
			BaseSelectAction,
			ETriggerEvent::Started,
			this,
			&ACollectorBattlePlayerController::OnBaseSelect);
	}
}

void ACollectorBattlePlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit) return;

	UpdateActorHighlighting(CursorHit.GetActor());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ACollectorBattlePlayerController::NextCamera()
{
	if (const IPlayerInterface* PlayerInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerInterface->Execute_SwitchCamera(GetPawn(), 1);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ACollectorBattlePlayerController::PreviousCamera()
{
	if (const IPlayerInterface* PlayerInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerInterface->Execute_SwitchCamera(GetPawn(), -1);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ACollectorBattlePlayerController::OnSelectRightActor()
{
	if (UDeckComponent* OwnerDeckComponent = GetPawn()->FindComponentByClass<UDeckComponent>())
	{
		UpdateActorHighlighting(OwnerDeckComponent->SelectNextCard(1));
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ACollectorBattlePlayerController::OnSelectLeftActor()
{
	if (UDeckComponent* OwnerDeckComponent = GetPawn()->FindComponentByClass<UDeckComponent>())
	{
		UpdateActorHighlighting(OwnerDeckComponent->SelectNextCard(-1));
	}
}

void ACollectorBattlePlayerController::OnBaseSelect(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();

	if (FMath::Abs(InputAxisVector.X) >= FMath::Abs(InputAxisVector.Y))
	{
		if (UDeckComponent* OwnerDeckComponent = GetPawn()->FindComponentByClass<UDeckComponent>())
		{
			UpdateActorHighlighting(OwnerDeckComponent->SelectNextCard(InputAxisVector.X > 0 ? 1 : -1));
		}
	}
	else
	{
		if (InputAxisVector.Y > 0)
		{
			NextCamera();
		}
		else
		{
			PreviousCamera();
		}
	}
}

void ACollectorBattlePlayerController::OnInputKeyPressed(const FKeyEvent& KeyEvent)
{
	// Keyboard or gamepad key was pressed so we hide the mouse cursor
	if (!bShowMouseCursor) return;

	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());
}

void ACollectorBattlePlayerController::OnMouseKeyPressed(const FPointerEvent&)
{
	if (bShowMouseCursor) return;

	SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());
}

void ACollectorBattlePlayerController::UpdateActorHighlighting(AActor* Actor)
{
	LastActor = ThisActor;
	ThisActor = Actor;

	if (LastActor != ThisActor)
	{
		UDeckComponent* OwnerDeckComponent = GetPawn()->FindComponentByClass<UDeckComponent>();
		if (LastActor && LastActor->Implements<UInteractionInterface>())
		{
			Cast<IInteractionInterface>(LastActor)->Unhighlight();
			if (OwnerDeckComponent) OwnerDeckComponent->SetHighlightedCard(nullptr);
		}
		if (ThisActor && ThisActor->Implements<UInteractionInterface>())
		{
			Cast<IInteractionInterface>(ThisActor)->Highlight();
			if (OwnerDeckComponent) OwnerDeckComponent->SetHighlightedCard(ThisActor);
		}
	}
}

void ACollectorBattlePlayerController::HandleMouseMovement()
{
	if (bShowMouseCursor) return;

	float MouseX, MouseY;
	if (GetMousePosition(MouseX, MouseY))
	{
		const FVector2D CurrentPos(MouseX, MouseY);

		float Distance = FVector2D::Distance(LastMousePos, CurrentPos);

		if (Distance > MouseMovementThreshold)
		{
			SetShowMouseCursor(true);
			SetInputMode(FInputModeGameAndUI());
		}

		LastMousePos = CurrentPos;
	}
}
