// Copyrights Plejady Team

#pragma once

#include "CoreMinimal.h"
#include "AwaitableObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinished);

/**
 * 
 */
UCLASS(BlueprintType)
class COLLECTOR_API UAwaitableObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintCallable)
	FOnFinished OnFinished;	
};
