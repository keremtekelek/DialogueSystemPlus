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

	VisitedNPC_Nodes.Empty();
	VisitedMC_Nodes.Empty();
	
	bool GraphHasNodes = false;
	
    for (UEdGraph* Graph : BP_DialogueWriter->UbergraphPages)
    {
    	if (Graph && Graph->Nodes.Num() > 0)
    	{
    			GraphHasNodes = true;
    			break;
    	}
    }
    
    if(!GraphHasNodes)
    {
		ClearDataTables();
    	UE_LOG(LogTemp, Warning, TEXT("Graph has no nodes. Data Tables are cleared"))
    	
    	return;
    }
    

	//
	for (UEdGraph* Graph : BP_DialogueWriter->UbergraphPages)
	{
		if (!Graph) continue;
		
		for (UEdGraphNode* Node : Graph->Nodes)
		{
			if (!IsValid(Node)) continue;
			
			bool IsRoot = false;

			UEdGraphPin* InputPin = Node->FindPin(UEdGraphSchema_K2::PN_Execute);

			if (!InputPin || InputPin->LinkedTo.Num() == 0)
			{
				IsRoot = true;
			}

			if (IsRoot)
			{
				// Handling NPC_Dialogue Node
				if (UNPC_DialogueNode* NPCNode = Cast<UNPC_DialogueNode>(Node))
				{
					bool bNeedsUpdate = false;
					if (NPCNode->DialogueID.IsNone())
					{
						bNeedsUpdate = true;
					}

					if (bNeedsUpdate)
					{
						NPCNode->Modify();
					}
					
					if (NPCNode->DialogueID.IsNone())
					{
						// **** Handling non-Automated Variables****

						//---DialogueText, RelatedGlobalEvents, DesiredNPC_Mood, OwnerOfNode---
						NPCNode->NPC_Row.DialogueText = NPCNode->DialogueText;
						NPCNode->NPC_Row.RelatedGlobalEvents = NPCNode->RelatedGlobalEvent;
						NPCNode->NPC_Row.DesiredNPC_Mood = NPCNode->DesiredNPC_Mood;
						NPCNode->NPC_Row.ConversationPartner = NPCNode->OwnerOfNode;

						//*** Handling Automated Variables***

						NPCNode->Modify();
						
						//---DialogueID--
						FGuid NodeID_GUID = NPCNode->NodeGuid;
						FString NodeID_string = NodeID_GUID.ToString();
						FName NodeID(*NodeID_string);
					
						NPCNode->NPC_Row.DialogueID = NodeID; 

						//---EndOfDialogue---
						UEdGraphPin* ExecPin = NPCNode->FindPin(UEdGraphSchema_K2::PN_Then);
						if (ExecPin && ExecPin->LinkedTo.Num() > 0) 
						{
							NPCNode->NPC_Row.EndOfDialogue = false;
						}
						else
						{
							NPCNode->NPC_Row.EndOfDialogue = true;
						}

						TravelAllChildNodes_NPCNode(NPCNode);
					
					}
					else
					{
						// ??
					}
				}

				// Handling MainnCharacterChoices Node
				else if (UMainCharacterChoices_Node* MainCharacterChoicesNode = Cast<UMainCharacterChoices_Node>(Node))
				{
				

					// **** Handling non-Automated Variables****

					//---Choice Text---
					MainCharacterChoicesNode->AllChoice_Row.Choice1.ChoiceText = MainCharacterChoicesNode->C1_ChoiceText;
					MainCharacterChoicesNode->AllChoice_Row.Choice2.ChoiceText = MainCharacterChoicesNode->C2_ChoiceText;
					MainCharacterChoicesNode->AllChoice_Row.Choice3.ChoiceText = MainCharacterChoicesNode->C3_ChoiceText;

				
					//---Related Global Events---
					MainCharacterChoicesNode->AllChoice_Row.Choice1.RelatedGlobalEvents = MainCharacterChoicesNode->C1_RelatedGlobalEvents;
					MainCharacterChoicesNode->AllChoice_Row.Choice2.RelatedGlobalEvents = MainCharacterChoicesNode->C2_RelatedGlobalEvents;
					MainCharacterChoicesNode->AllChoice_Row.Choice3.RelatedGlobalEvents = MainCharacterChoicesNode->C3_RelatedGlobalEvents;

				
					//---Effects Mood---
					MainCharacterChoicesNode->AllChoice_Row.Choice1.EffectsMood = MainCharacterChoicesNode->C1_EffectMood;
					MainCharacterChoicesNode->AllChoice_Row.Choice2.EffectsMood = MainCharacterChoicesNode->C2_EffectMood;
					MainCharacterChoicesNode->AllChoice_Row.Choice3.EffectsMood = MainCharacterChoicesNode->C3_EffectMood;

					//*** Handling Automated Variables***

					//---Choice ID---

					

					//---Choice ID 1---

					/*
					if (MainCharacterChoicesNode->AllChoice_Row.Choice1.ChoiceID1.IsNone())
					{
						
						MainCharacterChoicesNode->Modify(); 
					
						FGuid Choice1_guid = FGuid::NewGuid();
						
						MainCharacterChoicesNode->PersistentChoiceID1 = FName(*Choice1_guid.ToString());
						MainCharacterChoicesNode->AllChoice_Row.Choice1.ChoiceID1 = FName(*Choice1_guid.ToString());
					}*/

					if (MainCharacterChoicesNode->PersistentChoiceID1.IsNone())
					{
						MainCharacterChoicesNode->Modify();
						FGuid Choice1_guid = FGuid::NewGuid();
						MainCharacterChoicesNode->PersistentChoiceID1 = FName(*Choice1_guid.ToString());

						MainCharacterChoicesNode->AllChoice_Row.Choice1.ChoiceID1 = MainCharacterChoicesNode->PersistentChoiceID1;
					}
					
					

					//---Choice ID 2---
					if (MainCharacterChoicesNode->PersistentChoiceID1.IsNone())
					{
						MainCharacterChoicesNode->Modify();
						FGuid Choice2_guid = FGuid::NewGuid();
						MainCharacterChoicesNode->PersistentChoiceID2 = FName(*Choice2_guid.ToString());

						MainCharacterChoicesNode->AllChoice_Row.Choice2.ChoiceID2 = MainCharacterChoicesNode->PersistentChoiceID2;
					}
					
					

					//---Choice ID 3---
					if (MainCharacterChoicesNode->PersistentChoiceID3.IsNone())
					{
						MainCharacterChoicesNode->Modify();
						FGuid Choice3_guid = FGuid::NewGuid();
						MainCharacterChoicesNode->PersistentChoiceID3 = FName(*Choice3_guid.ToString());

						MainCharacterChoicesNode->AllChoice_Row.Choice3.ChoiceID3 = MainCharacterChoicesNode->PersistentChoiceID3;

					}
					
				
				


					UEdGraphPin* ExecPin = MainCharacterChoicesNode->FindPin(UEdGraphSchema_K2::PN_Then);  

					//---EndOfDialogue---
					if (ExecPin && ExecPin->LinkedTo.Num() > 0) 
					{
						MainCharacterChoicesNode->AllChoice_Row.Choice1.EndOfDialogue = false;
						MainCharacterChoicesNode->AllChoice_Row.Choice2.EndOfDialogue = false;
						MainCharacterChoicesNode->AllChoice_Row.Choice3.EndOfDialogue = false;
					}
					else
					{
						MainCharacterChoicesNode->AllChoice_Row.Choice1.EndOfDialogue = true;
						MainCharacterChoicesNode->AllChoice_Row.Choice2.EndOfDialogue = true;
						MainCharacterChoicesNode->AllChoice_Row.Choice3.EndOfDialogue = true;
					}

					TravelAllChildNodes_ChoiceNode(MainCharacterChoicesNode);
				
				}
			}
		}
	}

	ClearDataTables();
		
   
    for (UEdGraph* Graph : BP_DialogueWriter->UbergraphPages)
    {
        for (UEdGraphNode* Node : Graph->Nodes)
        {
           
            if (UNPC_DialogueNode* NPCNode = Cast<UNPC_DialogueNode>(Node))
            {
                UDataTable* TargetTable = nullptr;

                
                switch (NPCNode->NPC_Row.ConversationPartner)
                {
                    case EConversationPartner::AppleSeller:
                        TargetTable = DT_AppleSeller;
                        break;
                    case EConversationPartner::Baker:
                        TargetTable = DT_Baker;
                        break;
                    case EConversationPartner::Butcher:
                        TargetTable = DT_Butcher;
                        break;
					case EConversationPartner::LemonSeller:
                		TargetTable = DT_LemonSeller;
                		break;
					case EConversationPartner::PotatoSeller:
                		TargetTable = DT_PotatoSeller;
                		break;
                    
                }

                if (TargetTable)
                {
                   
                    TargetTable->AddRow(NPCNode->NPC_Row.DialogueID, NPCNode->NPC_Row);
                }
            }

            
            else if (UMainCharacterChoices_Node* MCNode = Cast<UMainCharacterChoices_Node>(Node))
            {
                if (DT_MainCharacter)
                {
                    // Choice 1
                    DT_MainCharacter->AddRow(MCNode->AllChoice_Row.Choice1.ChoiceID1, MCNode->AllChoice_Row);

                    // Choice 2
                    DT_MainCharacter->AddRow(MCNode->AllChoice_Row.Choice2.ChoiceID2, MCNode->AllChoice_Row);

                    // Choice 3
                    DT_MainCharacter->AddRow(MCNode->AllChoice_Row.Choice3.ChoiceID3, MCNode->AllChoice_Row);
                }
            }
        }
    }

   
	MarkDataTablesAsDirty();

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


void UDialogueWriter::TravelAllChildNodes_NPCNode(UNPC_DialogueNode* CurrentNode)
{
	
	
	FNPC_Dialogues NPC_Row;

	if (!CurrentNode || VisitedNPC_Nodes.Contains(CurrentNode))
	{
		return;
	}
	
	VisitedNPC_Nodes.Add(CurrentNode);

	if (UEdGraphPin* ExecPin = CurrentNode->FindPin(UEdGraphSchema_K2::PN_Then))
	{
		if (ExecPin && ExecPin->LinkedTo.Num() > 0)
		{
			for (UEdGraphPin* LinkedPin : ExecPin->LinkedTo)
			{
			
				if (LinkedPin && LinkedPin->GetOwningNode())
				{
					if (UMainCharacterChoices_Node* Next_MainCharacterChoicesNode = Cast<UMainCharacterChoices_Node>(LinkedPin->GetOwningNode()))
					{
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice1.RelatedNPC_Dialogues.Add(CurrentNode->NPC_Row.DialogueID);
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice2.RelatedNPC_Dialogues.Add(CurrentNode->NPC_Row.DialogueID);
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice3.RelatedNPC_Dialogues.Add(CurrentNode->NPC_Row.DialogueID);

						Next_MainCharacterChoicesNode->AllChoice_Row.Choice1.RelatedNPC_Dialogues.Append(CurrentNode->NPC_Row.RelatedNPC_Dialogues);
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice2.RelatedNPC_Dialogues.Append(CurrentNode->NPC_Row.RelatedNPC_Dialogues);
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice3.RelatedNPC_Dialogues.Append(CurrentNode->NPC_Row.RelatedNPC_Dialogues);

						
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice1.ConversationPartner = CurrentNode->NPC_Row.ConversationPartner;
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice2.ConversationPartner = CurrentNode->NPC_Row.ConversationPartner;
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice3.ConversationPartner = CurrentNode->NPC_Row.ConversationPartner;

						TravelAllChildNodes_ChoiceNode(Next_MainCharacterChoicesNode);
					}
				}
			}
		}
		
		
	}
}

void UDialogueWriter::TravelAllChildNodes_ChoiceNode(UMainCharacterChoices_Node* CurrentNode)
{
	if (!CurrentNode || VisitedMC_Nodes.Contains(CurrentNode))
	{
		return;
	}
	VisitedMC_Nodes.Add(CurrentNode);

	const TArray<FName> ChoicePinNames = { TEXT("Choice1"), TEXT("Choice2"), TEXT("Choice3") };

	for (int32 i = 0; i < ChoicePinNames.Num(); i++)
    {
        UEdGraphPin* OutputPin = CurrentNode->FindPin(ChoicePinNames[i]);

        
        if (OutputPin && OutputPin->LinkedTo.Num() > 0)
        {
            for (UEdGraphPin* LinkedPin : OutputPin->LinkedTo)
            {
                if (LinkedPin && LinkedPin->GetOwningNode())
                {
                    if (UNPC_DialogueNode* Next_NPCNode = Cast<UNPC_DialogueNode>(LinkedPin->GetOwningNode()))
                    {
                        
                        if (i == 0) // Choice1
                        {
                            Next_NPCNode->NPC_Row.RelatedNPC_Choices.Append(CurrentNode->AllChoice_Row.Choice1.RelatedNPC_Choices);
                            Next_NPCNode->NPC_Row.RelatedNPC_Dialogues.Append(CurrentNode->AllChoice_Row.Choice1.RelatedNPC_Dialogues); 
                            
                            
                            Next_NPCNode->NPC_Row.RelatedNPC_Choices.Add(CurrentNode->AllChoice_Row.Choice1.ChoiceID1);
                        }
                        else if (i == 1) // Choice 2
                        {
                            Next_NPCNode->NPC_Row.RelatedNPC_Choices.Append(CurrentNode->AllChoice_Row.Choice2.RelatedNPC_Choices);
                            Next_NPCNode->NPC_Row.RelatedNPC_Dialogues.Append( CurrentNode->AllChoice_Row.Choice2.RelatedNPC_Dialogues);
                            
                            Next_NPCNode->NPC_Row.RelatedNPC_Choices.Add(CurrentNode->AllChoice_Row.Choice2.ChoiceID2);
                        }
                        else if (i == 2) // Choice 3
                        {
                            Next_NPCNode->NPC_Row.RelatedNPC_Choices.Append(CurrentNode->AllChoice_Row.Choice3.RelatedNPC_Choices);
                            Next_NPCNode->NPC_Row.RelatedNPC_Dialogues.Append(CurrentNode->AllChoice_Row.Choice3.RelatedNPC_Dialogues);
                            
                            Next_NPCNode->NPC_Row.RelatedNPC_Choices.Add(CurrentNode->AllChoice_Row.Choice3.ChoiceID3);
                        }

                        TravelAllChildNodes_NPCNode(Next_NPCNode);
                    }
                    
                }
            }
        }
    }
}

void UDialogueWriter::ClearDataTables()
{
	if (DT_AppleSeller)
	{
		DT_AppleSeller->EmptyTable();
	}
	if (DT_Butcher)
	{
		DT_Butcher->EmptyTable();
	}
	if (DT_Baker)
	{
		DT_Baker->EmptyTable();
	}
	if (DT_LemonSeller)
	{
		DT_LemonSeller->EmptyTable();
	}
	if (DT_PotatoSeller)
	{
		DT_PotatoSeller->EmptyTable();
	}
	if (DT_MainCharacter)
	{
		DT_MainCharacter->EmptyTable();
	}
}

void UDialogueWriter::MarkDataTablesAsDirty()
{
	if (DT_AppleSeller)
	{
		DT_AppleSeller->MarkPackageDirty();
	}
	if (DT_Butcher)
	{
		DT_Butcher->MarkPackageDirty();
	}
	if (DT_Baker)
	{
		DT_Baker->MarkPackageDirty();
	}
	if (DT_LemonSeller)
	{
		DT_LemonSeller->MarkPackageDirty();
	}
	if (DT_PotatoSeller)
	{
		DT_PotatoSeller->MarkPackageDirty();
	}
	if (DT_MainCharacter)
	{
		DT_MainCharacter->MarkPackageDirty();
	}
}

