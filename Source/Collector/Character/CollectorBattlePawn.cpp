// Copyrights Plejady Team


#include "CollectorBattlePawn.h"

// Sets default values
ACollectorBattlePawn::ACollectorBattlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACollectorBattlePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectorBattlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACollectorBattlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

