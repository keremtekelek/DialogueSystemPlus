

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/Widget_MoodMeter.h"
#include "UI/Widget_Dialogue.h"
#include "ActorComponents/AC_DialogueSystem.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Structs/MainCharacter/S_MainCharacterChoices.h"
#include "Structs/NPC/S_NPC_Dialogues.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Enums/GlobalEnums.h"
#include "DialogueSystemPlusCharacter.h"
#include "Subsystem_Dialogue.generated.h"

class UAC_InteractionSystem;
class ADialogueSystemPlusCharacter;
class APlayerControllerCPP;


UENUM(BlueprintType)
enum class EScoreType : uint8
{
	Choice				UMETA(DisplayName = "Choice"),    
	Dialogue	        UMETA(DisplayName = "Dialogue")   
	  
};


/**
 * 
 */
UCLASS()
class DIALOGUESYSTEMPLUS_API USubsystem_Dialogue : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	

	//***VARIABLES***
public:

	
	
	// Actor Components
	UPROPERTY(EditAnywhere, Category = "Components")
	UAC_InteractionSystem* AC_InteractionSystem;

	UPROPERTY(EditAnywhere, Category = "Components")
	UAC_DialogueSystem* AC_DialogueSystem;
	

	// Widgets
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UWidget_MoodMeter* WBP_MoodMeter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UWidget_Dialogue* WBP_Dialogue;

	UPROPERTY()
	TSubclassOf<UWidget_Dialogue> DialogueWidgetClass;

	
	// NPC Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	UDataTable* DataTable_NPC;

	// DSM stands for "Dialogue Score Map".
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	TMap<FName, int32> DSM_NPC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	int MoodValue_NPC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	ENPCMood Mood_NPC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	EConversationPartner InteractedCharacter;


	// Main Character Data
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main Character Data")
	ADialogueSystemPlusCharacter* MainCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main Character Data")
	TMap<FName, int32> DSM_MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Character Data")
	UDataTable* DataTable_MainCharacter;


	// Processed Variables
	UPROPERTY(VisibleAnywhere)
	TArray<FName> ProcessedDialogues;

	UPROPERTY(VisibleAnywhere)
	TArray<FName> ProcessedChoices;

	UPROPERTY(VisibleAnywhere)
	TArray<FName> ProcessedGlobalEvents;

	// Score Values
	UPROPERTY(VisibleAnywhere)
	int DialogueScore_Value = 0;

	UPROPERTY(VisibleAnywhere)
	int ChoiceScore_Value = 0;

	
	//Best NPC Row Properties

	UPROPERTY()
	FName NPC_DialogueID;
	
	UPROPERTY()
	FText NPC_DialogueText;

	UPROPERTY()
	USoundBase* NPC_DialogueSound;

	UPROPERTY()
	bool NPC_EndOfDialogue;

	UPROPERTY()
	TArray<FName> NPC_EventsToTrigger;

	//Best Main Character Choice Row Properties

	UPROPERTY()
	FName Choice1_ID;

	UPROPERTY()
	FName Choice2_ID;

	UPROPERTY()
	FName Choice3_ID;


	
	UPROPERTY()
	FText Choice1_Text;

	UPROPERTY()
	FText Choice2_Text;

	UPROPERTY()
	FText Choice3_Text;

	UPROPERTY()
	bool Choice1_EndOfDialogue;

	UPROPERTY()
	bool Choice2_EndOfDialogue;

	UPROPERTY()
	bool Choice3_EndOfDialogue;

	UPROPERTY()
	TArray<FName> Choice1_EventsToTrigger;

	UPROPERTY()
	TArray<FName> Choice2_EventsToTrigger;

	UPROPERTY()
	TArray<FName> Choice3_EventsToTrigger;

	UPROPERTY()
	int Choice1_EffectsMood;

	UPROPERTY()
	int Choice2_EffectsMood;

	UPROPERTY()
	int Choice3_EffectsMood;

	// Timer variables
	FTimerHandle DelayShowChoiceHandle;
	FTimerHandle DelayCloseDialogueHandle;
	

	//Chosen Button
	UPROPERTY()
	EChosenOption ChosenChoice = EChosenOption::None;

	// Player Controller	

	UPROPERTY()
	APlayerControllerCPP* PlayerController;
	

	//***FUNCTIONS***
public:

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interacted();

	UFUNCTION(BlueprintCallable)
	void GettingVariables();

	UFUNCTION(BlueprintCallable)
	void StartDialogue();

	UFUNCTION(BlueprintCallable)
	void ContinueDialogue();

	UFUNCTION(BlueprintCallable)
	void FinishDialogue();

	UFUNCTION(BlueprintCallable, Category = "Dialogue Scoring")
	FName ScoreMC_Choices();

	UFUNCTION(BlueprintCallable, Category = "Dialogue Scoring")
	FName ScoreNPC_Dialogues();

	UFUNCTION(BlueprintCallable, Category = "Dialogue Scoring")
	void AddScoreValue(int ScoreToAdd, EScoreType ScoreType);

	UFUNCTION(BlueprintCallable, Category = "Dialogue Scoring")
	void GetBestDialogue_RowProperties(const FNPC_Dialogues& BestNPC_Row);

	UFUNCTION(BlueprintCallable, Category = "Dialogue Scoring")
	void GetBestChoice_RowProperties(const FMainCharacterChoices& BestMC_Row);

	UFUNCTION(BlueprintCallable, Category = "Dialogue Scoring")
	bool FilterDialogues();

	
	

	UFUNCTION(BlueprintCallable, Category = "Timer Functions")
	void ShowChoiceAfterSeconds();

	UFUNCTION(BlueprintCallable, Category = "Timer Functions")
	void CloseDialogueAfterSeconds();

	UFUNCTION(BlueprintCallable)
	void MakeChoice(EChosenOption ChosenButton);


	// DEBUG

	UFUNCTION()
	static void PrintString(const FString& Message, float time, FColor Color);
	
};



