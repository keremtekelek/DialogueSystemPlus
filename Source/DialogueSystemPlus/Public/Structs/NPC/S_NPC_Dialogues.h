#pragma once
 
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/GlobalEnums.h"
#include "Sound/SoundBase.h"
#include "GameplayTagContainer.h"
#include "S_NPC_Dialogues.generated.h"


USTRUCT(BlueprintType)
struct FNPC_Dialogues : public FTableRowBase
{
	GENERATED_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* DialogueSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer RelatedGlobalEvents;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer EventsToTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	EConversationPartner ConversationPartner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENPCMood DesiredNPC_Mood;
	
	
	// Auto Generated Dialogue Data
	UPROPERTY(BlueprintReadOnly, Category="Auto Generated Dialogue Data") 
	FName DialogueID;
	
	UPROPERTY(BlueprintReadOnly, Category="Auto Generated Dialogue Data") 
	TArray<FName> RelatedNPC_Dialogues;

	UPROPERTY(BlueprintReadOnly, Category="Auto Generated Dialogue Data") 
	FName NextDialogueID;
	
	UPROPERTY(BlueprintReadOnly, Category="Auto Generated Dialogue Data") 
	FName NextChoiceID;
	
	UPROPERTY(BlueprintReadOnly, Category="Auto Generated Dialogue Data") 
	bool IsRoot;
	
	UPROPERTY(BlueprintReadOnly, Category="Auto Generated Dialogue Data") 
	bool EndOfDialogue;
	
};


USTRUCT(BlueprintType)
struct FDisturb : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisturbText;
	
};




 
