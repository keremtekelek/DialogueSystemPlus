

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "Structs/MainCharacter/S_MainCharacterChoices.h"
#include "EdGraphSchema_K2.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "MainCharacterChoices_Node.generated.h"

class UDialogueWriter;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class DIALOGUESYSTEMPLUS_API UMainCharacterChoices_Node : public UK2Node
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, Category = "Choice 1 Data")
	FText C1_ChoiceText;

	UPROPERTY(EditAnywhere, Category = "Choice 1 Data")
	int32 C1_EffectMood;

	UPROPERTY(EditAnywhere, Category = "Choice 1 Data")
	TArray<FName> C1_RelatedGlobalEvents;

	

	
	UPROPERTY(EditAnywhere, Category = "Choice 2 Data")
	FText C2_ChoiceText;

	UPROPERTY(EditAnywhere, Category = "Choice 2 Data")
	int32 C2_EffectMood;

	UPROPERTY(EditAnywhere, Category = "Choice 2 Data")
	TArray<FName> C2_RelatedGlobalEvents;

	

	
	UPROPERTY(EditAnywhere, Category = "Choice 3 Data")
	FText C3_ChoiceText;

	UPROPERTY(EditAnywhere, Category = "Choice 3 Data")
	int32 C3_EffectMood;

	UPROPERTY(EditAnywhere, Category = "Choice 3 Data")
	TArray<FName> C3_RelatedGlobalEvents;



	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Generated Choice 1 Data")
	TArray<FName> C1_RelatedNPC_Dialogues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Generated Choice 1 Data")
	TArray<FName> C1_RelatedNPC_Choices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Generated Choice 1 Data")
	bool C1_EndOfDialogue = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Generated Choice 1 Data")
	EConversationPartner C1_ConversationPartner;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Generated Choice 2 Data")
	TArray<FName> C2_RelatedNPC_Dialogues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Generated Choice 2 Data")
	TArray<FName> C2_RelatedNPC_Choices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Generated Choice 2 Data")
	bool C2_EndOfDialogue = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Generated Choice 2 Data")
	EConversationPartner C2_ConversationPartner;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Generated Choice 3 Data")
	TArray<FName> C3_RelatedNPC_Dialogues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Generated Choice 3 Data")
	TArray<FName> C3_RelatedNPC_Choices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Generated Choice 3 Data")
	bool C3_EndOfDialogue = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Generated Choice 3 Data")
	EConversationPartner C3_ConversationPartner;

	
	

public:
	
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void AllocateDefaultPins() override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual FText GetMenuCategory() const override;
	virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;

	
	virtual bool ShouldShowNodeProperties() const override { return true; }
	
	
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(0.1f, 0.6f, 0.2f); }
};
	
