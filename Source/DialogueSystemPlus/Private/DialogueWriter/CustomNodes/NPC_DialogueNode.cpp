#include "DialogueWriter/CustomNodes/NPC_DialogueNode.h"
#include "DialogueWriter/DialogueWriter.h"
#include "DialogueWriter/CustomNodes/MainCharacterChoices_Node.h"

#define LOCTEXT_NAMESPACE "NPC_DialogueNode"

UNPC_DialogueNode::UNPC_DialogueNode()
{
	FGuid dialogueID_guid = FGuid::NewGuid();
	this->NPC_Row.DialogueID = FName(*dialogueID_guid.ToString());
}


FText UNPC_DialogueNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	
	return LOCTEXT("NodeTitle", "NPC Dialogue Node");
}

void UNPC_DialogueNode::AllocateDefaultPins()
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	/*
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);

	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);*/

	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, FDialogueFlow::StaticStruct(), UEdGraphSchema_K2::PN_Execute);

	
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
	
}

void UNPC_DialogueNode::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);
		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UNPC_DialogueNode::GetMenuCategory() const
{
	return LOCTEXT("MenuCategory", "Dialogue System");
}

bool UNPC_DialogueNode::IsCompatibleWithGraph(const UEdGraph* TargetGraph) const
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

bool UNPC_DialogueNode::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
	/*
	if (MyPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Exec)
	{
		
		UK2Node* OtherNode = Cast<UK2Node>(OtherPin->GetOwningNode());

		
		bool IsChoiceNode = OtherNode && OtherNode->IsA(UMainCharacterChoices_Node::StaticClass());
		
		bool IsNPCNode = OtherNode && OtherNode->IsA(UNPC_DialogueNode::StaticClass());

		
		if (!IsChoiceNode && !IsNPCNode)
		{
			OutReason = TEXT("NPC Node can only connects with Choice Node!");
			return true; 
		}

	return Super::IsConnectionDisallowed(MyPin, OtherPin, OutReason);
	}*/

	if (MyPin->Direction == EGPD_Input && MyPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
	{
		UK2Node* OtherNode = Cast<UK2Node>(OtherPin->GetOwningNode());

		
		bool bIsChoice = OtherNode && OtherNode->IsA(UMainCharacterChoices_Node::StaticClass());
		
		bool bIsNPC = OtherNode && OtherNode->IsA(UNPC_DialogueNode::StaticClass());

		if (!bIsChoice && !bIsNPC)
		{
			OutReason = TEXT("Blocked");
			return true; 
		}
	}

	
	else if (MyPin->Direction == EGPD_Output && MyPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Exec)
	{
		UK2Node* OtherNode = Cast<UK2Node>(OtherPin->GetOwningNode());

		
		bool bIsChoice = OtherNode && OtherNode->IsA(UMainCharacterChoices_Node::StaticClass());
		bool bIsNPC = OtherNode && OtherNode->IsA(UNPC_DialogueNode::StaticClass());

		if (!bIsChoice && !bIsNPC)
		{
			OutReason = TEXT("Blocked");
			return true; 
		}
	}

	return Super::IsConnectionDisallowed(MyPin, OtherPin, OutReason);

	
	
}

#undef LOCTEXT_NAMESPACE