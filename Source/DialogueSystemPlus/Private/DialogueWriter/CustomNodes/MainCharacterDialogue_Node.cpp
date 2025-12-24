#include "DialogueWriter/CustomNodes/MainCharacterDialogue_Node.h"
#include "DialogueWriter/DialogueWriter.h"
#include "DialogueWriter/CustomNodes/MainCharacterChoices_Node.h"
#include "DialogueWriter/CustomNodes/NPC_DialogueNode.h"

#define LOCTEXT_NAMESPACE "MainCharacterDialogue_Node"

UMainCharacterDialogue_Node::UMainCharacterDialogue_Node()
{
	FGuid dialogueID_guid = FGuid::NewGuid();
	this->MC_DialogueRow.DialogueID = FName(*dialogueID_guid.ToString());
}


FText UMainCharacterDialogue_Node::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("NodeTitle", "Player Dialogue Node");
}

void UMainCharacterDialogue_Node::AllocateDefaultPins()
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	

	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, FDialogueFlow::StaticStruct(), UEdGraphSchema_K2::PN_Execute);

	
	
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Struct, FDialogueFlow::StaticStruct(), UEdGraphSchema_K2::PN_Then);
	
}

void UMainCharacterDialogue_Node::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);
		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UMainCharacterDialogue_Node::GetMenuCategory() const
{
	return LOCTEXT("MenuCategory", "Dialogue System");
}

bool UMainCharacterDialogue_Node::IsCompatibleWithGraph(const UEdGraph* TargetGraph) const
{
	if (!TargetGraph)
	{
		return false;
	}

	
	UBlueprint* MyBlueprint = Cast<UBlueprint>(TargetGraph->GetOuter());
	if (!MyBlueprint || !MyBlueprint->GeneratedClass)
	{
		return false;
	}
		
	if (MyBlueprint->ParentClass->IsChildOf(UDialogueWriter::StaticClass()))
	{
		return true; 
	}

	return false;
}

bool UMainCharacterDialogue_Node::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
	if (MyPin->Direction == EGPD_Input && MyPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
	{
		UK2Node* OtherNode = Cast<UK2Node>(OtherPin->GetOwningNode());

		bool IsNPC = OtherNode && OtherNode->IsA(UNPC_DialogueNode::StaticClass());
		bool IsMC_DialogueNode = OtherNode && OtherNode->IsA(UMainCharacterDialogue_Node::StaticClass());

		if (!IsNPC && !IsMC_DialogueNode)
		{
			OutReason = TEXT("Blocked");
			return true; 
		}
	}

	
	else if (MyPin->Direction == EGPD_Output && MyPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
	{
		UK2Node* OtherNode = Cast<UK2Node>(OtherPin->GetOwningNode());

		bool IsNPC = OtherNode && OtherNode->IsA(UNPC_DialogueNode::StaticClass());
		bool IsMC_DialogueNode = OtherNode && OtherNode->IsA(UMainCharacterDialogue_Node::StaticClass());

		if (!IsNPC && !IsMC_DialogueNode)
		{
			OutReason = TEXT("Blocked");
			return true; 
		}
	}

	return Super::IsConnectionDisallowed(MyPin, OtherPin, OutReason);

}

void UMainCharacterDialogue_Node::PostEditImport()
{
	Super::PostEditImport();
	
	FGuid NewGuid = FGuid::NewGuid();
	this->MC_DialogueRow.DialogueID = FName(*NewGuid.ToString());
	
	this->MC_DialogueRow.RelatedNPC_Dialogues.Empty();
	this->MC_DialogueRow.RelatedNPC_Choices.Empty();
	this->MC_DialogueRow.IsRoot = false;
	this->MC_DialogueRow.EndOfDialogue = false;
}

#undef LOCTEXT_NAMESPACE