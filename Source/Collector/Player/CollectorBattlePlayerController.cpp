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
			SwitchCameraAction,
			ETriggerEvent::Started,
			this,
			&ACollectorBattlePlayerController::SwitchCamera);

		EnhancedInputComponent->BindAction(
			SelectRightActorAction,
			ETriggerEvent::Started,
			this,
			&ACollectorBattlePlayerController::OnSelectRightActor);

		EnhancedInputComponent->BindAction(
			SelectLeftActorAction,
			ETriggerEvent::Started,
			this,
			&ACollectorBattlePlayerController::OnSelectLeftActor);
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
void ACollectorBattlePlayerController::SwitchCamera()
{
	if (const IPlayerInterface* PlayerInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerInterface->Execute_SwitchCamera(GetPawn());
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

void ACollectorBattlePlayerController::OnInputKeyPressed(const FKeyEvent& KeyEvent)
{
	if (KeyEvent.GetKey().IsGamepadKey())
	{
		if (!bShowMouseCursor) return;

		SetShowMouseCursor(false);
		SetInputMode(FInputModeGameOnly());
	}
	else
	{
		if (bShowMouseCursor) return;

		SetShowMouseCursor(true);
		SetInputMode(FInputModeGameAndUI());
	}
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
