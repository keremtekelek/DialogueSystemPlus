#pragma once
 
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/GlobalEnums.h"
#include "S_NPC_Dialogues.generated.h"

USTRUCT(BlueprintType)
struct FNPC_Dialogues : public FTableRowBase
{
	GENERATED_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DialogueID;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DialogueText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> RelatedNPC_Dialogues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> RelatedNPC_Choices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> RelatedGlobalEvents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool EndOfDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConversationPartner ConversationPartner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENPCMood DesiredNPC_Mood;
};


 
