#include "Subsystems/Subsystem_Dialogue.h"
#include "DialogueSystemPlus.h"
#include "GameplayTagsManager.h"
#include "ActorComponents/AC_InteractionSystem.h"
#include "DialogueSystemPlusCharacter.h"
#include "PlayerController/PlayerControllerCPP.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Subsystems/Subsystem_EventManager.h"


void USubsystem_Dialogue::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	USubsystem_EventManager* eventSubsystem= Collection.InitializeDependency<USubsystem_EventManager>();

	if (eventSubsystem)
	{
		EventManager_Subsystem = eventSubsystem;
	}
	
	
	ProcessedChoices.Empty();
	ProcessedDialogues.Empty();
	ProcessedGlobalEvents.Reset();

	DSM_MainCharacter.Empty();
	DSM_NPC.Empty();
	
}

void USubsystem_Dialogue::Deinitialize()
{
	Super::Deinitialize();
}

void USubsystem_Dialogue::Tick(float DeltaTime)
{
	TimeSinceLastTick += DeltaTime;

	if (TimeSinceLastTick >= TickInterval)
	{
		//***WRITE CODES ABOUT TICK IN HERE!***

		if (EventManager_Subsystem)
		{
			ProcessedGlobalEvents = EventManager_Subsystem->TriggeredEvents;

			UE_LOG(LogTemp, Warning, TEXT("Processed Tags: %s"), *ProcessedGlobalEvents.ToStringSimple());
		}
		 
		TimeSinceLastTick -= TickInterval; 
	}
}

ETickableTickType USubsystem_Dialogue::GetTickableTickType() const
{
	return (IsTemplate() ? ETickableTickType::Never : ETickableTickType::Always);
}

TStatId USubsystem_Dialogue::GetStatId() const
{
	
	RETURN_QUICK_DECLARE_CYCLE_STAT(USubsystem_EventManager, STATGROUP_Tickables);
}





// This function works when interaction started with Main Character with NPC.
void USubsystem_Dialogue::Interacted()
{
	if (IsValid(AC_InteractionSystem) && AC_InteractionSystem->CanMainCharacterInteract == true)
	{
		GettingVariables();
		StartDialogue();
	}
}

// Starting Dialogue
void USubsystem_Dialogue::StartDialogue()
{
	ContinueDialogue();
}

// Getting useful variables from DialogueSystem
void USubsystem_Dialogue::GettingVariables()
{
	
	if (IsValid(AC_InteractionSystem) && IsValid(AC_InteractionSystem->AC_DialogueSystem))
	{
		AC_DialogueSystem = AC_InteractionSystem->AC_DialogueSystem;
		WBP_MoodMeter = AC_InteractionSystem->AC_DialogueSystem->WBP_MoodMeter;

		DataTable_NPC= AC_InteractionSystem->AC_DialogueSystem->DataTable_NPC;
		DSM_NPC = AC_InteractionSystem->AC_DialogueSystem->DSM_NPC;

		Mood_NPC = AC_InteractionSystem->AC_DialogueSystem->NPC_Mood;
		MoodValue_NPC = AC_InteractionSystem->AC_DialogueSystem->MoodValue;

		InteractedCharacter = AC_InteractionSystem->AC_DialogueSystem->InteractedCharacter;
	}
}

//Continue Dialogue
void USubsystem_Dialogue::ContinueDialogue()
{
	PrintString("Continue Dialogue has been called",2.f,FColor::Red);
	
	 if (FilterDialogues() == false)
	 {
	 	PrintString("Filter Dialogue has been failed", 2.f,FColor::Magenta);
		 return;
	 }
	
	//***Starting Dialogue***
	if (NPC_EndOfDialogue)
	{
		if (ProcessedDialogues.Contains(NPC_DialogueID))
		{
			return;
		}
		
		WBP_Dialogue->ShowDialogue(NPC_DialogueText);
		ProcessedDialogues.AddUnique(NPC_DialogueID);
		EventManager_Subsystem->TriggerEvent(NPC_EventsToTrigger);
		

		if (NPC_DialogueSound)
		{
			FVector SoundLocation = AC_DialogueSystem->OwnerLocation;
			UGameplayStatics::PlaySoundAtLocation(this, NPC_DialogueSound,SoundLocation);

			GetWorld()->GetTimerManager().SetTimer(DelayShowChoiceHandle,this, &USubsystem_Dialogue::CloseDialogueAfterSeconds,NPC_DialogueSound->Duration + 1.6f,false);
			
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(DelayCloseDialogueHandle,this, &USubsystem_Dialogue::CloseDialogueAfterSeconds,CalculateDialogueDuration(NPC_DialogueText),false);
			
		}
	}
	else
	{
		if (ProcessedDialogues.Contains(NPC_DialogueID))
		{
			return;
		}
		
		WBP_Dialogue->ShowDialogue(NPC_DialogueText);
		ProcessedDialogues.AddUnique(NPC_DialogueID);
		EventManager_Subsystem->TriggerEvent(NPC_EventsToTrigger);

		if (NPC_DialogueSound)
		{
			FVector SoundLocation = AC_DialogueSystem->OwnerLocation;
			UGameplayStatics::PlaySoundAtLocation(this, NPC_DialogueSound,SoundLocation);

			GetWorld()->GetTimerManager().SetTimer(DelayShowChoiceHandle,this, &USubsystem_Dialogue::ShowChoiceAfterSeconds,NPC_DialogueSound->Duration + 1.6f,false);

		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(DelayCloseDialogueHandle,this, &USubsystem_Dialogue::ShowChoiceAfterSeconds,CalculateDialogueDuration(NPC_DialogueText),false);
			
		}
	}
}

// Filtering Dialogues
bool USubsystem_Dialogue::FilterDialogues()
{
	FName BestNPC_DialogueRowName = ScoreNPC_Dialogues();

	if (BestNPC_DialogueRowName.IsNone())
	{
		//FinishDialogue();
		return false; 
	}
	else
	{
		FNPC_Dialogues* npcFoundRow = DataTable_NPC->FindRow<FNPC_Dialogues>(BestNPC_DialogueRowName,"");
		if (npcFoundRow)
		{
			GetBestDialogue_RowProperties(*npcFoundRow);
		}
		else
		{
			return false;
		}
	}
	
	
	
	FName BestChoice_RowName = ScoreMC_Choices();

	if (BestChoice_RowName.IsNone())
	{
		//FinishDialogue();
		return false; 
	}
	else
	{
		FMainCharacterChoices* FoundMC_Row = DataTable_MainCharacter->FindRow<FMainCharacterChoices>(BestChoice_RowName,"");
		if (FoundMC_Row)
		{
			GetBestChoice_RowProperties(*FoundMC_Row);
		}
		else
		{
			return false;
		}
	}
	
	return true;
}

void USubsystem_Dialogue::FinishDialogue()
{
	PrintString("Finish Dialogue has been called",2.f,FColor::Red);
	
	GetWorld()->GetTimerManager().ClearTimer(DelayShowChoiceHandle);
	GetWorld()->GetTimerManager().ClearTimer(DelayCloseDialogueHandle);
	
	while (PlayerController->IsMoveInputIgnored())
	{
		PlayerController->SetIgnoreMoveInput(false);
	}

	while (PlayerController->IsLookInputIgnored())
	{
		PlayerController->SetIgnoreLookInput(false);
	}
	
	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;
	
	WBP_Dialogue->CloseDialogue();
	WBP_Dialogue->CloseChoices();
	
	FSlateApplication::Get().SetAllUserFocusToGameViewport();
}


// Scoring Functions
FName USubsystem_Dialogue::ScoreMC_Choices()
{
	if (DataTable_MainCharacter)
	{
		TArray<FMainCharacterChoices*> ChoiceRows;

		DataTable_MainCharacter->GetAllRows("", ChoiceRows);

		for (const auto ChoiceRow: ChoiceRows)
		{
			ChoiceScore_Value = 0;
			
			// Only one choice struct is enough to score


			//Scoring Choices
			
			FGameplayTagContainer RequiredTags = ChoiceRow->Choice1.RelatedGlobalEvents;
        
			for (auto It = RequiredTags.CreateConstIterator(); It; ++It)
			{
				
				if (ProcessedGlobalEvents.HasTag(*It))
				{
					AddScoreValue(1, EScoreType::Choice);
				}
			}

			for (FName Choice1_Choices: ChoiceRow->Choice1.RelatedNPC_Choices)
			{
				if (ProcessedChoices.Contains(Choice1_Choices))
				{
					AddScoreValue(1,EScoreType::Choice);
				}
			}

			for (FName Choice1_Dialogues: ChoiceRow->Choice1.RelatedNPC_Dialogues)
			{
				if (ProcessedDialogues.Contains(Choice1_Dialogues))
				{
					AddScoreValue(1,EScoreType::Choice);
				}
			}

			if (InteractedCharacter == ChoiceRow->Choice1.ConversationPartner)
			{
				AddScoreValue(3,EScoreType::Choice);
			}

			//Adding Row name and score value to DSM_MainCharacter
			
			DSM_MainCharacter.Add(ChoiceRow->Choice1.ChoiceID1, ChoiceScore_Value);
		}

		FName BestChoiceID = NAME_None;
		int HighestScore = INT_MIN;

		// Finding Highest Score Row
		for (const auto& Pair : DSM_MainCharacter)
		{
			if (Pair.Value > HighestScore)
			{
				HighestScore = Pair.Value;
				BestChoiceID = Pair.Key;
			}
		}

		
		if (BestChoiceID != NAME_None)
		{
			UE_LOG(LogTemp, Log, TEXT("Best Choice: %s, Score: %d"), *BestChoiceID.ToString(), HighestScore);
		}

		DSM_MainCharacter.Empty();
		ChoiceScore_Value = 0;
		
		return BestChoiceID;
	}
	
	return NAME_None;
}

FName USubsystem_Dialogue::ScoreNPC_Dialogues()
{
	if (DataTable_NPC)
	{
		TArray<FNPC_Dialogues*> DialogueRows;

		DataTable_NPC->GetAllRows("", DialogueRows);

		for (const auto DialogueRow: DialogueRows)
		{
			DialogueScore_Value = 0;

			FGameplayTagContainer RequiredTags = DialogueRow->RelatedGlobalEvents;
        
			for (auto It = RequiredTags.CreateConstIterator(); It; ++It)
			{
				if (ProcessedGlobalEvents.HasTag(*It))
				{
					AddScoreValue(1, EScoreType::Dialogue);
				}
			}
			
			for (FName NPC_Choice: DialogueRow->RelatedNPC_Choices)
			{
				if (ProcessedChoices.Contains(NPC_Choice))
				{
					AddScoreValue(1,EScoreType::Dialogue);
				}
			}

			for (FName NPC_Dialogues: DialogueRow->RelatedNPC_Dialogues)
			{
				if (ProcessedDialogues.Contains(NPC_Dialogues))
				{
					AddScoreValue(1,EScoreType::Dialogue);
				}
			}

			if (Mood_NPC == DialogueRow->DesiredNPC_Mood)
			{
				AddScoreValue(1,EScoreType::Dialogue);
			}

			DSM_NPC.Add(DialogueRow->DialogueID, DialogueScore_Value);
			
		}

		FName BestDialogueID = NAME_None;
		int HighestScore = INT_MIN;

		// Finding Highest Score Row
		for (const auto& Pair : DSM_NPC)
		{
			if (Pair.Value > HighestScore)
			{
				HighestScore = Pair.Value;
				BestDialogueID = Pair.Key;
			}
		}

		if (BestDialogueID != NAME_None)
		{
			UE_LOG(LogTemp, Log, TEXT("Best Choice: %s, Score: %d"), *BestDialogueID.ToString(), HighestScore);
		}

		DSM_NPC.Empty();
		DialogueScore_Value = 0;
		
		return BestDialogueID;
	}

	return NAME_None;
}



// Getting Row Properties
void USubsystem_Dialogue::GetBestChoice_RowProperties(const FMainCharacterChoices& BestMC_Row)
{
	Choice1_ID = BestMC_Row.Choice1.ChoiceID1;
	Choice2_ID = BestMC_Row.Choice2.ChoiceID2;
	Choice3_ID = BestMC_Row.Choice3.ChoiceID3;

	Choice1_Text = BestMC_Row.Choice1.ChoiceText;
	Choice2_Text = BestMC_Row.Choice2.ChoiceText;
	Choice3_Text = BestMC_Row.Choice3.ChoiceText;

	Choice1_EffectsMood = BestMC_Row.Choice1.EffectsMood;
	Choice2_EffectsMood = BestMC_Row.Choice2.EffectsMood;
	Choice3_EffectsMood = BestMC_Row.Choice3.EffectsMood;

	Choice1_EndOfDialogue = BestMC_Row.Choice1.EndOfDialogue;
	Choice2_EndOfDialogue = BestMC_Row.Choice2.EndOfDialogue;
	Choice3_EndOfDialogue = BestMC_Row.Choice3.EndOfDialogue;

	Choice1_EventsToTrigger = BestMC_Row.Choice1.EventsToTrigger;
	Choice2_EventsToTrigger = BestMC_Row.Choice2.EventsToTrigger;
	Choice3_EventsToTrigger = BestMC_Row.Choice3.EventsToTrigger;
}

void USubsystem_Dialogue::GetBestDialogue_RowProperties(const FNPC_Dialogues& BestNPC_Row)
{
	NPC_DialogueID = BestNPC_Row.DialogueID;
	NPC_DialogueText = BestNPC_Row.DialogueText;
	NPC_DialogueSound = BestNPC_Row.DialogueSound;
	NPC_EndOfDialogue = BestNPC_Row.EndOfDialogue;
	NPC_EventsToTrigger = BestNPC_Row.EventsToTrigger;
}


// Adding Score Value
void USubsystem_Dialogue::AddScoreValue(int ScoreToAdd, EScoreType ScoreType)
{
	if (ScoreType == EScoreType::Choice)
	{
		ChoiceScore_Value += ScoreToAdd;
	}

	else if (ScoreType == EScoreType::Dialogue)
	{
		DialogueScore_Value += ScoreToAdd;
	}
}






void USubsystem_Dialogue::MakeChoice(EChosenOption ChosenButton)
{
	//ChosenChoice = ChosenButton;

	if (ChosenButton == EChosenOption::Choice1)
	{
		PrintString("Choice1 has been chosen",2.f,FColor::Red);
		
		if (Choice1_EndOfDialogue)
		{
			ProcessedChoices.AddUnique(Choice1_ID);
			
			FinishDialogue();
		}
		else
		{
			ProcessedChoices.Add(Choice1_ID);
			WBP_Dialogue->CloseChoices();
			ContinueDialogue();
		}
		
		AC_DialogueSystem->AddMoodValue(Choice1_EffectsMood);
		EventManager_Subsystem->TriggerEvent(Choice1_EventsToTrigger);
	}
	else if (ChosenButton == EChosenOption::Choice2)
	{
		PrintString("Choice2 has been chosen",2.f,FColor::Red);
		if (Choice2_EndOfDialogue)
		{
			ProcessedChoices.AddUnique(Choice2_ID);
			FinishDialogue();
		}
		else
		{
			ProcessedChoices.AddUnique(Choice2_ID);
			WBP_Dialogue->CloseChoices();
			ContinueDialogue();
		}
		AC_DialogueSystem->AddMoodValue(Choice2_EffectsMood);
		EventManager_Subsystem->TriggerEvent(Choice2_EventsToTrigger);
		
	}
	else if (ChosenButton == EChosenOption::Choice3)
	{
		PrintString("Choice3 has been chosen",2.f,FColor::Red);
		if (Choice3_EndOfDialogue)
		{
			ProcessedChoices.AddUnique(Choice3_ID);
			FinishDialogue();
		}
		else
		{
			ProcessedChoices.AddUnique(Choice3_ID);
			WBP_Dialogue->CloseChoices();
			ContinueDialogue();
		}
		AC_DialogueSystem->AddMoodValue(Choice3_EffectsMood);
		EventManager_Subsystem->TriggerEvent(Choice3_EventsToTrigger);
	}
}


float USubsystem_Dialogue::CalculateDialogueDuration(FText DialogueText)
{
	FString DialogueTextString = DialogueText.ToString();
	int DialogueLength = DialogueTextString.Len();
	
	float CalculatedDuration = (DialogueLength * 0.07f) + MinimumDialogueLength;
	
	return CalculatedDuration;
}


// Timer Functions
void USubsystem_Dialogue::ShowChoiceAfterSeconds()
{
	WBP_Dialogue->ShowChoices(Choice1_Text, Choice2_Text, Choice3_Text);
	
	PlayerController->SetIgnoreMoveInput(true);
	PlayerController->StopMovement();
	MainCharacter->GetCharacterMovement()->StopMovementImmediately();
	
	
	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(WBP_Dialogue->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;

	GetWorld()->GetTimerManager().ClearTimer(DelayShowChoiceHandle);

	PrintString("ShowChoiceAfterSeconds function has been called",2.f,FColor::Red);
}

void USubsystem_Dialogue::CloseDialogueAfterSeconds()
{
	WBP_Dialogue->CloseDialogue();
	FinishDialogue();

	GetWorld()->GetTimerManager().ClearTimer(DelayCloseDialogueHandle);
}


//DEBUG Functions

void USubsystem_Dialogue::PrintString(const FString& Message, float Time, FColor Color)
{
	if (!GEngine)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1,Time, Color, Message);
}





