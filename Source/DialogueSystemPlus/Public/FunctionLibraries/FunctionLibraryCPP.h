
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FunctionLibraryCPP.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEMPLUS_API UFunctionLibraryCPP : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Debug Functions")
	static void PrintScreen(const FString& Message, float time, FColor Color);
	
};
