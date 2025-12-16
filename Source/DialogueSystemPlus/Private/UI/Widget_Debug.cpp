#include "UI/Widget_Debug.h"
#include "Subsystems/Subsystem_Dialogue.h"
#include "Enums/GlobalEnums.h"

void UWidget_Debug::NativeConstruct()
{
    Super::NativeConstruct();

    if (UGameInstance* GI = GetGameInstance())
    {
       DialogueSubsystem = GI->GetSubsystem<USubsystem_Dialogue>();
    }

	Debug_Text->SetVisibility(ESlateVisibility::Visible);
	DebugBorder->SetVisibility(ESlateVisibility::Visible);

    GetWorld()->GetTimerManager().SetTimer(UpdateTimerHandle, this, &UWidget_Debug::UpdateDebugData, 0.2f, true);
}

void UWidget_Debug::NativeDestruct()
{
    Super::NativeDestruct();
    GetWorld()->GetTimerManager().ClearTimer(UpdateTimerHandle);
}

void UWidget_Debug::UpdateDebugData()
{
    if (DialogueSubsystem && Debug_Text)
    {
       FString DT_NPC_Name = TEXT("NONE");
       if (DialogueSubsystem->DataTable_NPC)
       {
           DT_NPC_Name = DialogueSubsystem->DataTable_NPC->GetName();
       }

       const UEnum* EnumPtrChar = StaticEnum<EConversationPartner>();
       FString InteractedCharacterStr = TEXT("Invalid");
       if (EnumPtrChar)
       {
           InteractedCharacterStr = EnumPtrChar->GetNameStringByValue((int64)DialogueSubsystem->InteractedCharacter);
       }

       const UEnum* EnumPtrChoice = StaticEnum<EChosenOption>();
       FString ChosenChoiceStr = TEXT("Invalid");
       if (EnumPtrChoice)
       {
           ChosenChoiceStr = EnumPtrChoice->GetNameStringByValue((int64)DialogueSubsystem->ChosenChoice);
       }
       
       TArray<FName>& ArrayDialogues = DialogueSubsystem->ProcessedDialogues; 
       FString Str_Dialogues = TEXT("{ ");
       for (int32 i = 0; i < ArrayDialogues.Num(); ++i)
       {
          Str_Dialogues += ArrayDialogues[i].ToString();
          if (i < ArrayDialogues.Num() - 1) Str_Dialogues += TEXT(", ");
       }
       Str_Dialogues += TEXT(" }");
       
       TArray<FName>& ArrayChoices = DialogueSubsystem->ProcessedChoices; 
       FString Str_Choices = TEXT("{ ");
       for (int32 i = 0; i < ArrayChoices.Num(); ++i)
       {
          Str_Choices += ArrayChoices[i].ToString();
          if (i < ArrayChoices.Num() - 1) Str_Choices += TEXT(", ");
       }
       Str_Choices += TEXT(" }");

       TArray<FName>& ArrayEvents = DialogueSubsystem->ProcessedGlobalEvents; 
       FString Str_Events = TEXT("{ ");
       for (int32 i = 0; i < ArrayEvents.Num(); ++i)
       {
          Str_Events += ArrayEvents[i].ToString();
          if (i < ArrayEvents.Num() - 1) Str_Events += TEXT(", ");
       }
       Str_Events += TEXT(" }");

       int32 DialogueScore_Value = DialogueSubsystem->DialogueScore_Value;
       int32 ChoiceScore_Value = DialogueSubsystem->ChoiceScore_Value;

    	FText choicetext = DialogueSubsystem->NPC_DialogueText;
    	FString NPC_DialogueText = choicetext.ToString();
    	

       FString FinalText = FString::Printf(TEXT(
          "--- DEBUG DASHBOARD ---\n"
          "NPC Data Table       : %s\n"
          "Interacted Character : %s\n"
          "NPC Dialogue Text    : %s\n"
          "Dialogue Score       : %d\n"
          "Choice Score         : %d\n"
          "Chosen Choice        : %s\n"
          "Processed Dialogues  : %s\n"
          "Processed Choices    : %s\n"
          "Global Events        : %s\n"
          "-----------------------"
          ), 
          *DT_NPC_Name, 
          *InteractedCharacterStr,
          *NPC_DialogueText,
          DialogueScore_Value, 
          ChoiceScore_Value, 
          *ChosenChoiceStr, 
          *Str_Dialogues, 
          *Str_Choices, 
          *Str_Events 
          );

       Debug_Text->SetText(FText::FromString(FinalText));
    }
}