#include "DialogueWriter/DialogueWriter.h"
#include  "DialogueWriter/CustomNodes/NPC_DialogueNode.h"
#include "DialogueWriter/CustomNodes/MainCharacterChoices_Node.h"

#if WITH_EDITOR
#include "Engine/Blueprint.h"
#include "Kismet2/KismetEditorUtilities.h" 
#endif

void UDialogueWriter::GenerateDialogueData()
{
#if WITH_EDITOR
	
	UBlueprint* BP_DialogueWriter = Cast<UBlueprint>(this->GetClass()->ClassGeneratedBy);

	if (!(IsValid(BP_DialogueWriter)))
	{
		UE_LOG(LogTemp, Warning, TEXT("BP_DialogueWriter is not valid!"))
		return;
	}

	// Handling NPC_Dialogue Node
	for (UEdGraph* Graph : BP_DialogueWriter->UbergraphPages)
	{
		for (UEdGraphNode* Node : Graph->Nodes)
		{
			if (UNPC_DialogueNode* NPCNode = Cast<UNPC_DialogueNode>(Node))
			{
				FNPC_Dialogues NPC_Row;

				// **** Handling non-Automated Variables****

				NPC_Row.DialogueText = NPCNode->DialogueText;
				NPC_Row.RelatedGlobalEvents = NPCNode->RelatedGlobalEvent;
				NPC_Row.DesiredNPC_Mood = NPCNode->DesiredNPC_Mood;
				NPC_Row.ConversationPartner = NPCNode->OwnerOfNode;

				//*** Handling Automated Variables***
				
				FGuid NodeID_GUID = NPCNode->NodeGuid;
				FString NodeID_string = NodeID_GUID.ToString();
				FName NodeID(*NodeID_string);
				NPC_Row.DialogueID = NodeID; //DialogueID

				UEdGraphPin* ExecPin = NPCNode->FindPin(UEdGraphSchema_K2::PN_Then);  
				
				if (ExecPin && ExecPin->LinkedTo.Num() > 0) //EndOfConversation
				{
					NPC_Row.EndOfDialogue = false;
				}
				else
				{
					NPC_Row.EndOfDialogue = true;
				}
			}

			// Handling MainnCharacterChoices Node
			if (UMainCharacterChoices_Node* MainCharacterChoicesNode = Cast<UMainCharacterChoices_Node>(Node))
			{
				FMainCharacterChoices MainCharacterChoices;
				FChoice1 Choice1_row;
				FChoice2 Choice2_row;
				FChoice3 Choice3_row;
				
				MainCharacterChoices.Choice1 = Choice1_row;
				MainCharacterChoices.Choice2 = Choice2_row;
				MainCharacterChoices.Choice3 = Choice3_row;

				// **** Handling non-Automated Variables****

				//---Choice Text---
				Choice1_row.ChoiceText = MainCharacterChoicesNode->C1_ChoiceText;
				Choice2_row.ChoiceText = MainCharacterChoicesNode->C2_ChoiceText;
				Choice3_row.ChoiceText = MainCharacterChoicesNode->C3_ChoiceText;

				//---Related Global Events---
				Choice1_row.RelatedGlobalEvents = MainCharacterChoicesNode->C1_RelatedGlobalEvents;
				Choice2_row.RelatedGlobalEvents = MainCharacterChoicesNode->C2_RelatedGlobalEvents;
				Choice3_row.RelatedGlobalEvents = MainCharacterChoicesNode->C3_RelatedGlobalEvents;

				//---Effects Mood---
				Choice1_row.EffectsMood = MainCharacterChoicesNode->C1_EffectMood;
				Choice2_row.EffectsMood = MainCharacterChoicesNode->C2_EffectMood;
				Choice3_row.EffectsMood = MainCharacterChoicesNode->C3_EffectMood;

				//*** Handling Automated Variables***

				//---Choice ID---
				FGuid Choice1_guid = FGuid::NewGuid();
				FString Choice1_string = Choice1_guid.ToString();
				FName NodeID(*Choice1_string);

				FGuid Choice2_guid = FGuid::NewGuid();
				FString Choice2_string = Choice1_guid.ToString();
				FName NodeID2(*Choice1_string);

				FGuid Choice3_guid = FGuid::NewGuid();
				FString Choice3_string = Choice1_guid.ToString();
				FName NodeID3(*Choice1_string);
				
				Choice1_row.ChoiceID1 = NodeID;  
				Choice2_row.ChoiceID2 = NodeID2;
				Choice3_row.ChoiceID3 = NodeID3;


				UEdGraphPin* ExecPin = MainCharacterChoicesNode->FindPin(UEdGraphSchema_K2::PN_Then);  

				//---EndOfDialogue---
				if (ExecPin && ExecPin->LinkedTo.Num() > 0) 
				{
					Choice1_row.EndOfDialogue = false;
					Choice2_row.EndOfDialogue = false;
					Choice3_row.EndOfDialogue = false;
				}
				else
				{
					Choice1_row.EndOfDialogue = false;
					Choice2_row.EndOfDialogue = false;
					Choice3_row.EndOfDialogue = false;
				}
				
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("GenerateDialogueData Worked!"));
#endif
}

void UDialogueWriter::PostInitProperties()
{
	Super::PostInitProperties();

#if WITH_EDITOR
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		UClass* MyClass = GetClass();
		FString ClassName = MyClass->GetName();

		
		if (ClassName.StartsWith(TEXT("SKEL_")))
		{
			return;
		}

		
		if (ClassName.StartsWith(TEXT("REINST_")))
		{
			return;
		}

		if (UBlueprint* BP = Cast<UBlueprint>(MyClass->ClassGeneratedBy))
		{
			if (!BP->OnCompiled().IsBoundToObject(this))
			{
				BP->OnCompiled().AddUObject(this, &UDialogueWriter::OnBlueprintCompiled);
			}
		}
	}
#endif
}

// OnBlueprintCompiled Event
#if WITH_EDITOR
void UDialogueWriter::OnBlueprintCompiled(UBlueprint* InBlueprint)
{
	
    
	if (InBlueprint->GeneratedClass != GetClass())
	{
		return;
	}

	GenerateDialogueData();
}
#endif