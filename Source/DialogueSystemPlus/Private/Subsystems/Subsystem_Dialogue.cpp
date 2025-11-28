#include "Subsystems/Subsystem_Dialogue.h"

#include "GameplayTagsManager.h"
#include "ActorComponents/AC_InteractionSystem.h"


void USubsystem_Dialogue::Initialize(FSubsystemCollectionBase& Collection)
{
	MainCharacter = Cast<ADialogueSystemPlusCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	// Getting useful variables from Main Character.
	if (IsValid(MainCharacter))
	{
		DataTable_MainCharacter = MainCharacter->DataTable_MainCharacter;
		DSM_MainCharacter = MainCharacter->DSM_MainCharacter;
	}

	// Getting WBP_Dialogue
	if (DialogueWidgetClass)
	{
		WBP_Dialogue = CreateWidget<UWidget_Dialogue>(GetWorld(),DialogueWidgetClass);
		if (WBP_Dialogue)
		{
			WBP_Dialogue->AddToViewport();
		}
	}
}

void USubsystem_Dialogue::Deinitialize()
{
	
}


// This function works when interaction started with Main Character with NPC.
void USubsystem_Dialogue::Interacted()
{
	if (IsValid(AC_InteractionSystem) && AC_InteractionSystem->CanMainCharacterInteract == true)
	{
		GettingVariables();

		
	}
}


// Getting useful variables
void USubsystem_Dialogue::GettingVariables()
{
	//Getting variables from DialogueSystem
	if (IsValid(AC_InteractionSystem->AC_DialogueSystem))
	{
		AC_DialogueSystem = AC_InteractionSystem->AC_DialogueSystem;
		WBP_MoodMeter = AC_InteractionSystem->AC_DialogueSystem->WBP_MoodMeter;

		DataTable_NPC= AC_InteractionSystem->AC_DialogueSystem->DataTable_NPC;
		DSM_NPC = AC_InteractionSystem->AC_DialogueSystem->DSM_NPC;

		Mood_NPC = AC_InteractionSystem->AC_DialogueSystem->NPC_Mood;
		MoodValue_NPC = AC_InteractionSystem->AC_DialogueSystem->MoodValue;
	}
}

