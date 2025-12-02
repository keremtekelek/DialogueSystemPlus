
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
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class DIALOGUESYSTEMPLUS_API UNPC_DialogueNode : public UK2Node
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Struct")
	FNPC_Dialogues NPC_Row;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Data")
	FText DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Dialogue Data")
	USoundBase* DialogueSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Dialogue Data")
	TArray<FName> RelatedGlobalEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Dialogue Data")
	ENPCMood DesiredNPC_Mood;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Dialogue Data")
	EConversationPartner OwnerOfNode;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Dialogue Data")
	FName DialogueID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Dialogue Data")
	TArray<FName> RelatedNPC_Dialogues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Dialogue Data")
	TArray<FName> RelatedNPC_Choices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Dialogue Data")
	bool EndOfDialogue;

public:

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	
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
