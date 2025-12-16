#include "FunctionLibraries/FunctionLibraryCPP.h"

void UFunctionLibraryCPP::PrintScreen(const FString& Message, float time, FColor Color)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, time, Color, Message);
	}
}

