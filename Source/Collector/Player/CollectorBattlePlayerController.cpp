// Copyrights Plejady Team

#include "CollectorBattlePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Collector/AwaitableObject.h"
#include "Collector/Components/DeckComponent.h"
#include "Collector/Interface/InteractionInterface.h"

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
			BaseSelectAction,
			ETriggerEvent::Started,
			this,
			&ACollectorBattlePlayerController::OnBaseSelect);

		EnhancedInputComponent->BindAction(
			PickActorAction,
			ETriggerEvent::Started,
			this,
			&ACollectorBattlePlayerController::PickActor);

		EnhancedInputComponent->BindAction(
			CancelPickingAction,
			ETriggerEvent::Started,
			this,
			&ACollectorBattlePlayerController::CancelPicking);
	}
}

void ACollectorBattlePlayerController::CursorTrace()
{
	if (IsPickedActorMoving) return;

	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit)
	{
		if (LastActor && LastActor->Implements<UInteractionInterface>())
		{
			UDeckComponent* OwnerDeckComponent = GetPawn()->FindComponentByClass<UDeckComponent>();
			Cast<IInteractionInterface>(LastActor)->Unhighlight();
			if (OwnerDeckComponent) OwnerDeckComponent->SetHighlightedCard(nullptr);

			LastActor = nullptr;
			ThisActor = nullptr;
		}
		return;
	}

	UpdateActorHighlighting(CursorHit.GetActor());
}

void ACollectorBattlePlayerController::OnBaseSelect(const FInputActionValue& InputActionValue)
{
	if (IsActorPicked || IsPickedActorMoving) return;

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
		// TODO: Switch to slots/hand
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ACollectorBattlePlayerController::PickActor()
{
	if (IsPickedActorMoving
		|| IsActorPicked
		|| !IsValid(ThisActor)
		|| !ThisActor->Implements<UInteractionInterface>())
	{
		return;
	}

	PickedActor = ThisActor;
	ThisActor = nullptr;
	IsActorPicked = true;
	IsPickedActorMoving = true;

	UAwaitableObject* PickActorCallback = NewObject<UAwaitableObject>();
	PickActorCallback->OnFinished.AddDynamic(this, &ACollectorBattlePlayerController::OnActorPickingFinished);
	IInteractionInterface::Execute_Pick(PickedActor, PickActorCallback);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ACollectorBattlePlayerController::CancelPicking()
{
	if (IsPickedActorMoving ||
		!IsActorPicked
		|| !IsValid(PickedActor)
		|| !PickedActor->Implements<UInteractionInterface>())
	{
		return;
	}

	IsPickedActorMoving = true;
	UAwaitableObject* CancelingCallback = NewObject<UAwaitableObject>();
	CancelingCallback->OnFinished.AddDynamic(this, &ACollectorBattlePlayerController::OnActorCancelingFinished);
	IInteractionInterface::Execute_CancelPicking(PickedActor, CancelingCallback);

	IsActorPicked = false;
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
		if (FVector2D::Distance(LastMousePos, CurrentPos) > MouseMovementThreshold)
		{
			SetShowMouseCursor(true);
			SetInputMode(FInputModeGameAndUI());
		}

		LastMousePos = CurrentPos;
	}
}

void ACollectorBattlePlayerController::OnActorCancelingFinished()
{
	UpdateActorHighlighting(PickedActor);
	IsPickedActorMoving = false;
	PickedActor = nullptr;
}

void ACollectorBattlePlayerController::OnActorPickingFinished()
{
	IsPickedActorMoving = false;
}
