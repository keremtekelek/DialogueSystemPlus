#pragma once
 
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/GlobalEnums.h"
#include "Sound/SoundBase.h"
#include "S_NPC_Dialogues.generated.h"

USTRUCT(BlueprintType)
struct FNPC_Dialogues : public FTableRowBase
{
	GENERATED_BODY()
 
	UPROPERTY(EditAnywhere,Category="Auto Generated Dialogue Data") // auto  +
	FName DialogueID;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* DialogueSound;
	
	UPROPERTY(EditAnywhere,Category="Auto Generated Dialogue Data") // auto
	TArray<FName> RelatedNPC_Dialogues;

	UPROPERTY(EditAnywhere,Category="Auto Generated Dialogue Data") // auto
	TArray<FName> RelatedNPC_Choices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> RelatedGlobalEvents;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> EventsToTrigger;

	UPROPERTY(EditAnywhere,Category="Auto Generated Dialogue Data") // auto  +
	bool EndOfDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	EConversationPartner ConversationPartner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENPCMood DesiredNPC_Mood;
};


 
