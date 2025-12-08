#include "DialogueWriter/CustomNodes/MainCharacterChoices_Node.h"
#include "DialogueWriter/DialogueWriter.h"


#define LOCTEXT_NAMESPACE "MainCharacterChoices_Node"


UMainCharacterChoices_Node::UMainCharacterChoices_Node()
{
	//this->Modify();
	
	// Choice ID
	FGuid Choice1_guid = FGuid::NewGuid();
	FGuid Choice2_guid = FGuid::NewGuid();
	FGuid Choice3_guid = FGuid::NewGuid();
	
	this->AllChoice_Row.Choice1.ChoiceID1 = FName(*Choice1_guid.ToString());
	this->AllChoice_Row.Choice2.ChoiceID2 = FName(*Choice2_guid.ToString());
	this->AllChoice_Row.Choice3.ChoiceID3 = FName(*Choice3_guid.ToString());
	
}


FText UMainCharacterChoices_Node::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("NodeTitle", "Main Character Choices Node");
}

void UMainCharacterChoices_Node::AllocateDefaultPins()
{
	
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);

	UEdGraphPin* C1 = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TEXT("Choice1"));
	C1->PinFriendlyName = LOCTEXT("C1_Label", "Choice 1"); 


	UEdGraphPin* C2 = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TEXT("Choice2"));
	C2->PinFriendlyName = LOCTEXT("C2_Label", "Choice 2");


	UEdGraphPin* C3 = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TEXT("Choice3"));
	C3->PinFriendlyName = LOCTEXT("C3_Label", "Choice 3");
}

void UMainCharacterChoices_Node::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);
		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UMainCharacterChoices_Node::GetMenuCategory() const
{
	return LOCTEXT("MenuCategory", "Dialogue System");
}

bool UMainCharacterChoices_Node::IsCompatibleWithGraph(const UEdGraph* TargetGraph) const
{
	if (!TargetGraph)
	{
		return false;
	}
	
	
	UBlueprint* MyBlueprint = Cast<UBlueprint>(TargetGraph->GetOuter());
	if (!MyBlueprint || !MyBlueprint->ParentClass)
	{
		return false;
	}

	if (MyBlueprint->ParentClass->IsChildOf(UDialogueWriter::StaticClass()))
	{
		return true;
	}
	
	return false;
}

#undef LOCTEXT_NAMESPACE