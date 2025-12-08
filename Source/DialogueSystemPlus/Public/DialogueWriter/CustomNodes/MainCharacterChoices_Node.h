

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
	
	UMainCharacterChoices_Node();

public:
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Choice Struct")
	FMainCharacterChoices AllChoice_Row;

public:
	
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void AllocateDefaultPins() override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual FText GetMenuCategory() const override;
	virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;

	
	virtual bool ShouldShowNodeProperties() const override { return true; }
	
	
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(0.1f, 0.6f, 0.2f); }
};
	
