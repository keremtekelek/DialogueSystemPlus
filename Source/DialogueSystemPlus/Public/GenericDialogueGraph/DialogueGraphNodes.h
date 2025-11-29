#pragma once

#include "CoreMinimal.h"
#include "GenericGraphNode.h"
#include "Enums/GlobalEnums.h"
#include "Structs/MainCharacter/S_MainCharacterChoices.h"
#include "Structs/NPC/S_NPC_Dialogues.h"
#include "DialogueGraphNodes.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEMPLUS_API UDialogueGraphNodes : public UGenericGraphNode
{
	GENERATED_BODY()

public:

	
public:

	
	virtual FLinearColor GetBackgroundColor() const override { return FLinearColor(0.1f, 0.1f, 0.8f); }
	
};

UCLASS()
class DIALOGUESYSTEMPLUS_API UChoice_GraphNode : public UGenericGraphNode
{
	GENERATED_BODY()

public:
	
	

	virtual FText GetNodeTitle() const override { return FText::FromString("Player Choices"); }
	
	virtual FLinearColor GetBackgroundColor() const override { return FLinearColor(0.8f, 0.1f, 0.1f); }
};
