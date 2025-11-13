// Copyrights Plejady Team

#pragma once

#include "CoreMinimal.h"
#include "Collector/AwaitableObject.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLLECTOR_API IInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Highlight() = 0;	
	virtual void Unhighlight() = 0;

	UFUNCTION(BlueprintImplementableEvent)
	void Pick(const UAwaitableObject* CallbackObject);

	UFUNCTION(BlueprintImplementableEvent)
	void CancelPicking(const UAwaitableObject* CallbackObject);
};
