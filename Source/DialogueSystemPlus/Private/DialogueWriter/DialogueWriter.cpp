#include "DialogueWriter/DialogueWriter.h"
#include  "DialogueWriter/CustomNodes/NPC_DialogueNode.h"
#include "DialogueWriter/CustomNodes/MainCharacterChoices_Node.h"
#include "DialogueWriter/CustomNodes/MainCharacterDialogue_Node.h"

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
	VisitedMC_DialogueNodes.Empty();
	RootNPC_Nodes.Empty(); // Can be changed
	ActiveIDs.Empty(); 
	
	// Checking for if graph has some nodes.
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
	
	
	// Checking for illegal root(especially for root choice node)
	bool FoundIllegalRoot = false;

	for (UEdGraph* Graph : BP_DialogueWriter->UbergraphPages)
	{
		if (!Graph) continue;

		
		for (UEdGraphNode* Node : Graph->Nodes)
		{
			
			if (UMainCharacterChoices_Node* ChoiceNode = Cast<UMainCharacterChoices_Node>(Node))
			{
				
				UEdGraphPin* InputPin = ChoiceNode->FindPin(UEdGraphSchema_K2::PN_Execute);

				
				if (InputPin && InputPin->LinkedTo.Num() == 0)
				{
					UE_LOG(LogTemp, Error, TEXT("ERROR: Choice Node not cannot be Root node."))

					FText ErrorMsg = FText::FromString(TEXT("ERROR: Choice Node cannot be Root node"));
					FMessageDialog::Open(EAppMsgType::Ok, ErrorMsg);
					FoundIllegalRoot = true;
				}
			}
			else if (UMainCharacterDialogue_Node* MC_DialogueNode = Cast<UMainCharacterDialogue_Node>(Node))
			{
				UEdGraphPin* InputPin =  MC_DialogueNode->FindPin(UEdGraphSchema_K2::PN_Execute);

				if (InputPin && InputPin->LinkedTo.Num() == 0)
				{
					UE_LOG(LogTemp, Error, TEXT("ERROR: Player Dialogue Node not cannot be Root node."))

					FText ErrorMsg = FText::FromString(TEXT("ERROR: Player Dialogue Node not cannot be Root node."));
					FMessageDialog::Open(EAppMsgType::Ok, ErrorMsg);
					FoundIllegalRoot = true;
				}
			}
		}
	}

	if (FoundIllegalRoot)
	{
		UE_LOG(LogTemp, Error, TEXT("Dialogue Data Generation aborted due to illegal root!"));
		return; //can be edited
	}
    
	
	
	// Getting Root NPC Nodes
	for (UEdGraph* Graph : BP_DialogueWriter->UbergraphPages)
	{
		if (!Graph)
		{
			continue;
		}
		
		for (UEdGraphNode* Node : Graph->Nodes)
		{
			if (!IsValid(Node))
			{
				continue;
			}
			
			if (UNPC_DialogueNode* NPCNode = Cast<UNPC_DialogueNode>(Node))
			{
				bool IsRoot = false;
				
				UEdGraphPin* InputPin = NPCNode->FindPin(UEdGraphSchema_K2::PN_Execute);
			
				if (!InputPin || InputPin->LinkedTo.Num() == 0)
				{
					IsRoot = true;
				
					RootNPC_Nodes.Add(NPCNode);
				}
			}
		}
	}
			
	for (UNPC_DialogueNode* Node : RootNPC_Nodes)
	{
		Node->NPC_Row.IsRoot = true;
		HandleAutomatedData(Node);
	}

	CleanGhostNodesFromTables();
		
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







void UDialogueWriter::HandleAutomatedData(UEdGraphNode* HandledNode)
{
	if (UNPC_DialogueNode* NPCNode = Cast<UNPC_DialogueNode>(HandledNode))
	{
		if (!NPCNode || VisitedNPC_Nodes.Contains(NPCNode))
		{
			return;
		}
		VisitedNPC_Nodes.Add(NPCNode);
		
		ActiveIDs.Add(NPCNode->NPC_Row.DialogueID);
		
		UEdGraphPin* ExecPin = NPCNode->FindPin(UEdGraphSchema_K2::PN_Then);
		if (ExecPin && ExecPin->LinkedTo.Num() > 0) 
		{
			NPCNode->NPC_Row.EndOfDialogue = false;
			
			for (UEdGraphPin* LinkedPin : ExecPin->LinkedTo)
			{
				if (LinkedPin && LinkedPin->GetOwningNode())
				{
					if (UMainCharacterChoices_Node* Next_MainCharacterChoicesNode = Cast<UMainCharacterChoices_Node>(LinkedPin->GetOwningNode()))
					{
						
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice1.RelatedNPC_Dialogues.AddUnique(NPCNode->NPC_Row.DialogueID);
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice2.RelatedNPC_Dialogues.AddUnique(NPCNode->NPC_Row.DialogueID);
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice3.RelatedNPC_Dialogues.AddUnique(NPCNode->NPC_Row.DialogueID);
						
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice1.ConversationPartner = NPCNode->NPC_Row.ConversationPartner;
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice2.ConversationPartner = NPCNode->NPC_Row.ConversationPartner;
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice3.ConversationPartner = NPCNode->NPC_Row.ConversationPartner;

						for (const FName& IncomingID : NPCNode->NPC_Row.RelatedNPC_Dialogues)
						{
							Next_MainCharacterChoicesNode->AllChoice_Row.Choice1.RelatedNPC_Dialogues.AddUnique(IncomingID);
							Next_MainCharacterChoicesNode->AllChoice_Row.Choice2.RelatedNPC_Dialogues.AddUnique(IncomingID);
							Next_MainCharacterChoicesNode->AllChoice_Row.Choice3.RelatedNPC_Dialogues.AddUnique(IncomingID);
						}
						
						for (const FName& IncomingID : NPCNode->NPC_Row.RelatedNPC_Choices)
						{
							Next_MainCharacterChoicesNode->AllChoice_Row.Choice1.RelatedNPC_Choices.AddUnique(IncomingID);
							Next_MainCharacterChoicesNode->AllChoice_Row.Choice2.RelatedNPC_Choices.AddUnique(IncomingID);
							Next_MainCharacterChoicesNode->AllChoice_Row.Choice3.RelatedNPC_Choices.AddUnique(IncomingID);
						}
						
						const FGameplayTagContainer& IncomingTags = NPCNode->NPC_Row.RelatedGlobalEvents;
						
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice1.RelatedGlobalEvents.AppendTags(IncomingTags);
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice2.RelatedGlobalEvents.AppendTags(IncomingTags);
						Next_MainCharacterChoicesNode->AllChoice_Row.Choice3.RelatedGlobalEvents.AppendTags(IncomingTags);
						
						AddToDataTable(NPCNode);
						HandleAutomatedData(Next_MainCharacterChoicesNode); 
					}
					else if (UNPC_DialogueNode* Next_NPCNode = Cast<UNPC_DialogueNode>(LinkedPin->GetOwningNode()))
					{
						NPCNode->NPC_Row.NextDialogueID = Next_NPCNode->NPC_Row.DialogueID;
						
						Next_NPCNode->NPC_Row.ConversationPartner = NPCNode->NPC_Row.ConversationPartner;
						Next_NPCNode->NPC_Row.RelatedGlobalEvents.AppendTags(NPCNode->NPC_Row.RelatedGlobalEvents);
						Next_NPCNode->NPC_Row.RelatedNPC_Dialogues.AddUnique(NPCNode->NPC_Row.DialogueID);
						
						for (const FName& IncomingID : NPCNode->NPC_Row.RelatedNPC_Dialogues)
						{
							Next_NPCNode->NPC_Row.RelatedNPC_Dialogues.AddUnique(IncomingID);
						}
						for (const FName& IncomingID : NPCNode->NPC_Row.RelatedNPC_Choices)
						{
							Next_NPCNode->NPC_Row.RelatedNPC_Choices.AddUnique(IncomingID);
						}
						
						AddToDataTable(NPCNode);
						HandleAutomatedData(Next_NPCNode);
					}
					else if (UMainCharacterDialogue_Node* Next_PlayerDialogueNode = Cast<UMainCharacterDialogue_Node>(LinkedPin->GetOwningNode()))
					{
						NPCNode->NPC_Row.NextDialogueID = Next_PlayerDialogueNode->MC_DialogueRow.DialogueID;
						
						Next_PlayerDialogueNode->MC_DialogueRow.ConversationPartner = NPCNode->NPC_Row.ConversationPartner;
						Next_PlayerDialogueNode->MC_DialogueRow.RelatedGlobalEvents.AppendTags(NPCNode->NPC_Row.RelatedGlobalEvents);
						Next_PlayerDialogueNode->MC_DialogueRow.RelatedNPC_Dialogues.AddUnique(NPCNode->NPC_Row.DialogueID);
						
						for (const FName& IncomingID : NPCNode->NPC_Row.RelatedNPC_Dialogues)
						{
							Next_PlayerDialogueNode->MC_DialogueRow.RelatedNPC_Dialogues.AddUnique(IncomingID);
						}
						for (const FName& IncomingID : NPCNode->NPC_Row.RelatedNPC_Choices)
						{
							Next_PlayerDialogueNode->MC_DialogueRow.RelatedNPC_Choices.AddUnique(IncomingID);
						}
						
						AddToDataTable(NPCNode);
						HandleAutomatedData(Next_PlayerDialogueNode);
					}
				}
			}
		}
		else
		{
			NPCNode->NPC_Row.EndOfDialogue = true;
			AddToDataTable(NPCNode);
		}
		
	}
	
	else if (UMainCharacterChoices_Node* MainCharacterChoicesNode = Cast<UMainCharacterChoices_Node>(HandledNode))
	{
		if (!MainCharacterChoicesNode || VisitedMC_Nodes.Contains(MainCharacterChoicesNode))
		{
			return;
		}
		VisitedMC_Nodes.Add(MainCharacterChoicesNode);
		ActiveIDs.Add(MainCharacterChoicesNode->AllChoice_Row.Choice1.ChoiceID1);
		
		const TArray<FName> ChoicePinNames = { TEXT("Choice1"), TEXT("Choice2"), TEXT("Choice3") };
		
		
		
		for (int32 i = 0; i < ChoicePinNames.Num(); i++)
		{
			UEdGraphPin* OutputPin = MainCharacterChoicesNode->FindPin(ChoicePinNames[i]);
			
			if (OutputPin && OutputPin->LinkedTo.Num() > 0)
			{
				MainCharacterChoicesNode->AllChoice_Row.Choice1.EndOfDialogue = false;
				MainCharacterChoicesNode->AllChoice_Row.Choice2.EndOfDialogue = false;
				MainCharacterChoicesNode->AllChoice_Row.Choice3.EndOfDialogue = false;
				
				for (UEdGraphPin* LinkedPin : OutputPin->LinkedTo)
				{
					if (LinkedPin && LinkedPin->GetOwningNode())
					{
						if (UNPC_DialogueNode* Next_NPCNode = Cast<UNPC_DialogueNode>(LinkedPin->GetOwningNode()))
						{
							if (i == 0) // Choice1
							{
								Next_NPCNode->NPC_Row.RelatedNPC_Choices.AddUnique(MainCharacterChoicesNode->AllChoice_Row.Choice1.ChoiceID1);
								
								for (const FName& IncomingID : MainCharacterChoicesNode->AllChoice_Row.Choice1.RelatedNPC_Dialogues)
								{
									Next_NPCNode->NPC_Row.RelatedNPC_Dialogues.AddUnique(IncomingID);
								}
								
								for (const FName& IncomingID : MainCharacterChoicesNode->AllChoice_Row.Choice1.RelatedNPC_Choices)
								{
									Next_NPCNode->NPC_Row.RelatedNPC_Choices.AddUnique(IncomingID);
								}
								
								const FGameplayTagContainer& IncomingTags = MainCharacterChoicesNode->AllChoice_Row.Choice1.RelatedGlobalEvents;
								Next_NPCNode->NPC_Row.RelatedGlobalEvents.AppendTags(IncomingTags);
								
								
								Next_NPCNode->NPC_Row.ConversationPartner = MainCharacterChoicesNode->AllChoice_Row.Choice1.ConversationPartner;
								
							}
							
							else if (i == 1) // Choice 2
							{
								Next_NPCNode->NPC_Row.RelatedNPC_Choices.AddUnique(MainCharacterChoicesNode->AllChoice_Row.Choice2.ChoiceID2);
								
								for (const FName& IncomingID : MainCharacterChoicesNode->AllChoice_Row.Choice2.RelatedNPC_Dialogues)
								{
									Next_NPCNode->NPC_Row.RelatedNPC_Dialogues.AddUnique(IncomingID);
								}
								
								for (const FName& IncomingID : MainCharacterChoicesNode->AllChoice_Row.Choice2.RelatedNPC_Choices)
								{
									Next_NPCNode->NPC_Row.RelatedNPC_Choices.AddUnique(IncomingID);
								}
								
								const FGameplayTagContainer& IncomingTags = MainCharacterChoicesNode->AllChoice_Row.Choice2.RelatedGlobalEvents;
								Next_NPCNode->NPC_Row.RelatedGlobalEvents.AppendTags(IncomingTags);
								
								Next_NPCNode->NPC_Row.ConversationPartner = MainCharacterChoicesNode->AllChoice_Row.Choice1.ConversationPartner;
							}
							
							else if (i == 2) // Choice 3
							{
								Next_NPCNode->NPC_Row.RelatedNPC_Choices.AddUnique(MainCharacterChoicesNode->AllChoice_Row.Choice3.ChoiceID3);
								
								for (const FName& IncomingID : MainCharacterChoicesNode->AllChoice_Row.Choice3.RelatedNPC_Dialogues)
								{
									Next_NPCNode->NPC_Row.RelatedNPC_Dialogues.AddUnique(IncomingID);
								}
								
								for (const FName& IncomingID : MainCharacterChoicesNode->AllChoice_Row.Choice3.RelatedNPC_Choices)
								{
									Next_NPCNode->NPC_Row.RelatedNPC_Choices.AddUnique(IncomingID);
								}
								const FGameplayTagContainer& IncomingTags = MainCharacterChoicesNode->AllChoice_Row.Choice3.RelatedGlobalEvents;
								Next_NPCNode->NPC_Row.RelatedGlobalEvents.AppendTags(IncomingTags);
								
								Next_NPCNode->NPC_Row.ConversationPartner = MainCharacterChoicesNode->AllChoice_Row.Choice1.ConversationPartner;
							}
							
							AddToDataTable(MainCharacterChoicesNode);
							HandleAutomatedData(Next_NPCNode);
						}
					}
				}
			}
			else
			{
				//AddToDataTable(MainCharacterChoicesNode);
				
				MainCharacterChoicesNode->AllChoice_Row.Choice1.EndOfDialogue = true;
				MainCharacterChoicesNode->AllChoice_Row.Choice2.EndOfDialogue = true;
				MainCharacterChoicesNode->AllChoice_Row.Choice3.EndOfDialogue = true;
			}
		}
	}
	else if (UMainCharacterDialogue_Node* MainCharacterDialogueNode = Cast<UMainCharacterDialogue_Node>(HandledNode))
	{
		if (!MainCharacterDialogueNode || VisitedMC_DialogueNodes.Contains(MainCharacterDialogueNode))
		{
			return;
		}
		VisitedMC_DialogueNodes.Add(MainCharacterDialogueNode);
		
		ActiveIDs.Add(MainCharacterDialogueNode->MC_DialogueRow.DialogueID);

		UEdGraphPin* ExecPin = MainCharacterDialogueNode->FindPin(UEdGraphSchema_K2::PN_Then);
		if (ExecPin && ExecPin->LinkedTo.Num() > 0) 
		{
			MainCharacterDialogueNode->MC_DialogueRow.EndOfDialogue = false;
			
			for (UEdGraphPin* LinkedPin : ExecPin->LinkedTo)
			{
				if (LinkedPin && LinkedPin->GetOwningNode())
				{
					if (UNPC_DialogueNode* Next_NPCNode = Cast<UNPC_DialogueNode>(LinkedPin->GetOwningNode()))
					{
						MainCharacterDialogueNode->MC_DialogueRow.NextDialogueID = Next_NPCNode->NPC_Row.DialogueID;
						
						Next_NPCNode->NPC_Row.ConversationPartner = MainCharacterDialogueNode->MC_DialogueRow.ConversationPartner;
						Next_NPCNode->NPC_Row.RelatedGlobalEvents.AppendTags(MainCharacterDialogueNode->MC_DialogueRow.RelatedGlobalEvents);
						Next_NPCNode->NPC_Row.RelatedNPC_Dialogues.AddUnique(MainCharacterDialogueNode->MC_DialogueRow.DialogueID);
						
						for (const FName& IncomingID : MainCharacterDialogueNode->MC_DialogueRow.RelatedNPC_Dialogues)
						{
							Next_NPCNode->NPC_Row.RelatedNPC_Dialogues.AddUnique(IncomingID);
						}
						for (const FName& IncomingID : MainCharacterDialogueNode->MC_DialogueRow.RelatedNPC_Choices)
						{
							Next_NPCNode->NPC_Row.RelatedNPC_Choices.AddUnique(IncomingID);
						}
						
						AddToDataTable(MainCharacterDialogueNode);
						HandleAutomatedData(Next_NPCNode);
					}
					else if (UMainCharacterDialogue_Node* Next_PlayerDialogueNode = Cast<UMainCharacterDialogue_Node>(HandledNode))
					{
						MainCharacterDialogueNode->MC_DialogueRow.NextDialogueID = Next_PlayerDialogueNode->MC_DialogueRow.DialogueID;
						
						Next_PlayerDialogueNode->MC_DialogueRow.ConversationPartner = MainCharacterDialogueNode->MC_DialogueRow.ConversationPartner;
						Next_PlayerDialogueNode->MC_DialogueRow.RelatedGlobalEvents.AppendTags(MainCharacterDialogueNode->MC_DialogueRow.RelatedGlobalEvents);
						Next_PlayerDialogueNode->MC_DialogueRow.RelatedNPC_Dialogues.AddUnique(MainCharacterDialogueNode->MC_DialogueRow.DialogueID);
						
						for (const FName& IncomingID : MainCharacterDialogueNode->MC_DialogueRow.RelatedNPC_Dialogues)
						{
							Next_PlayerDialogueNode->MC_DialogueRow.RelatedNPC_Dialogues.AddUnique(IncomingID);
						}
						for (const FName& IncomingID : MainCharacterDialogueNode->MC_DialogueRow.RelatedNPC_Choices)
						{
							Next_PlayerDialogueNode->MC_DialogueRow.RelatedNPC_Choices.AddUnique(IncomingID);
						}
						
						AddToDataTable(MainCharacterDialogueNode);
						HandleAutomatedData(Next_PlayerDialogueNode);
					}
				}
			}
		}
		else
		{
			MainCharacterDialogueNode->MC_DialogueRow.EndOfDialogue = true;
			AddToDataTable(MainCharacterDialogueNode);
		}
	}
}


//Data Table Functions

void UDialogueWriter::AddToDataTable(UEdGraphNode* NodeToAddDataTable)
{
	if (UNPC_DialogueNode* NPCNode = Cast<UNPC_DialogueNode>(NodeToAddDataTable))
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
			FNPC_Dialogues FinalData = NPCNode->NPC_Row;

			for (const FName& ManualID : NPCNode->ManualAdded_RelatedNPC_Dialogues)
			{
				FinalData.RelatedNPC_Dialogues.AddUnique(ManualID);
			}

			
			FName RowName = FinalData.DialogueID;

			if (TargetTable->GetRowMap().Contains(RowName))
			{
				FNPC_Dialogues* ExistingRow = TargetTable->FindRow<FNPC_Dialogues>(RowName, "");
				*ExistingRow = FinalData;
			}
			else
			{
				TargetTable->AddRow(RowName, FinalData);
			}
		}
	}
	else if (UMainCharacterChoices_Node* MainCharacterChoicesNode = Cast<UMainCharacterChoices_Node>(NodeToAddDataTable))
	{
		FName RowName = MainCharacterChoicesNode->AllChoice_Row.Choice1.ChoiceID1;

		if (DT_MainCharacter->GetRowMap().Contains(RowName))
		{
			FMainCharacterChoices* ExistingRow = DT_MainCharacter->FindRow<FMainCharacterChoices>(RowName, "");
			if (ExistingRow)
			{
				*ExistingRow = MainCharacterChoicesNode->AllChoice_Row;
			}
		}
		else
		{
			DT_MainCharacter->AddRow(MainCharacterChoicesNode->AllChoice_Row.Choice1.ChoiceID1, MainCharacterChoicesNode->AllChoice_Row);
		}
		
	}
	else if (UMainCharacterDialogue_Node* MainCharacterDialoguesNode = Cast<UMainCharacterDialogue_Node>(NodeToAddDataTable))
	{
		FName RowName = MainCharacterDialoguesNode->MC_DialogueRow.DialogueID;

		if (DT_MainCharacterDialogues->GetRowMap().Contains(RowName))
		{
			FNPC_Dialogues* ExistingRow = DT_MainCharacterDialogues->FindRow<FNPC_Dialogues>(RowName, "");
			if (ExistingRow)
			{
				*ExistingRow = MainCharacterDialoguesNode->MC_DialogueRow;
			}
		}
		else
		{
			DT_MainCharacterDialogues->AddRow(MainCharacterDialoguesNode->MC_DialogueRow.DialogueID, MainCharacterDialoguesNode->MC_DialogueRow);
		}
	}
}

void UDialogueWriter::ClearDataTables()
{
	TArray<UDataTable*> AllTables = { DT_AppleSeller, DT_Baker, DT_Butcher, DT_LemonSeller, DT_PotatoSeller, DT_MainCharacter, DT_MainCharacterDialogues };

	for (UDataTable* Table : AllTables)
	{
		if (Table)
		{
			Table->EmptyTable();
		}
	}
}

void UDialogueWriter::MarkDataTablesAsDirty()
{
	TArray<UDataTable*> AllTables = { DT_AppleSeller, DT_Baker, DT_Butcher, DT_LemonSeller, DT_PotatoSeller, DT_MainCharacter, DT_MainCharacterDialogues };

	for (UDataTable* Table : AllTables)
	{
		if (Table)
		{
			Table->MarkPackageDirty();

			FDataTableEditorUtils::BroadcastPostChange(Table, FDataTableEditorUtils::EDataTableChangeInfo::RowList);
		}
	}
}

void UDialogueWriter::CleanGhostNodesFromTables()
{
	TArray<UDataTable*> AllTables = { DT_AppleSeller, DT_Baker, DT_Butcher, DT_LemonSeller, DT_PotatoSeller, DT_MainCharacter, DT_MainCharacterDialogues };
	
	for (UDataTable* Table : AllTables)
	{
		if (!Table) continue;

		
		TArray<FName> RowsToRemove;
        
		
		TArray<FName> RowNames = Table->GetRowNames();

		for (const FName& RowName : RowNames)
		{
			
			if (!ActiveIDs.Contains(RowName))
			{
				RowsToRemove.Add(RowName);
			}
		}

		for (const FName& RowToRemove : RowsToRemove)
		{
			Table->RemoveRow(RowToRemove);
		}
	}
}
