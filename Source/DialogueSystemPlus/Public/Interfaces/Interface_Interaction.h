

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_Interaction.generated.h"


UINTERFACE(MinimalAPI)
class UInterface_Interaction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DIALOGUESYSTEMPLUS_API IInterface_Interaction
{
	GENERATED_BODY()

	
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact();

	
};
