// Copyright Epic Games, Inc. All Rights Reserved.

#include "DialogueSystemPlusGameMode.h"
#include "DialogueSystemPlusCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADialogueSystemPlusGameMode::ADialogueSystemPlusGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/01_MyContent/Blueprints/Characters/MainCharacter/BP_MainCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
