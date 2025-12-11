
#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "Structs/NPC/S_NPC_Dialogues.h"
#include "EdGraphSchema_K2.h"
#include "Engine/Blueprint.h"
#include "BlueprintActionDatabaseRegistrar.h" 
#include "BlueprintNodeSpawner.h"
#include "NPC_DialogueNode.generated.h"

class UDialogueWriter;
class UMainCharacterChoices_Node;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class DIALOGUESYSTEMPLUS_API UNPC_DialogueNode : public UK2Node
{
	GENERATED_BODY()
	
public:
	
	UNPC_DialogueNode();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Struct")
	FNPC_Dialogues NPC_Row;
	
public:

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;
	
	virtual void AllocateDefaultPins() override;


	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	
	virtual FText GetMenuCategory() const override;
	
	virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;

	virtual FLinearColor GetNodeTitleColor() const override 
	{ 
		return FLinearColor(0.2f, 0.2f, 0.8f); 
	}

	virtual bool ShouldShowNodeProperties() const override { return true; }
};
