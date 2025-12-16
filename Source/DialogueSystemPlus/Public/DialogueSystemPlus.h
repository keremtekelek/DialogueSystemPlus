
#pragma once

#include "CoreMinimal.h"
#include "FunctionLibraries/FunctionLibraryCPP.h"


static FORCEINLINE void PrintScreen(FString Text, float Time = 2.0f, FColor Color = FColor::Magenta)
{
	
	UFunctionLibraryCPP::PrintScreen(Text, Time, Color);
}