// Copyrights Plejady Team

#pragma once

#include "CoreMinimal.h"
#include "Collector/AwaitableObject.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

// NOTE: Order is important here
UENUM(BlueprintType)
enum class ECameraPosition : uint8
{
	None,
	Hand,
	Middle,
	Table
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLLECTOR_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FTransform GetPickedCardTransform();
};
