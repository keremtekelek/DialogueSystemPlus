

#include "DialogueSystemPlusGameMode.h"
#include "DialogueSystemPlusCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADialogueSystemPlusGameMode::ADialogueSystemPlusGameMode()
{
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/01_MyContent/Blueprints/Characters/MainCharacter/BP_MainCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = APlayerControllerCPP::StaticClass();
}
