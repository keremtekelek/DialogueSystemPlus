#pragma once
 
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/GlobalEnums.h"
#include "GameplayTagContainer.h"
#include "S_MainCharacterChoices.generated.h"


USTRUCT(BlueprintType)
struct FChoice1
{
	GENERATED_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ChoiceText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EffectsMood = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer RelatedGlobalEvents;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer EventsToTrigger;

	UPROPERTY(BlueprintReadOnly,Category="Auto Generated Choice Data") // auto
	bool EndOfDialogue = false;

	UPROPERTY(BlueprintReadOnly,Category="Auto Generated Choice Data") // auto
	EConversationPartner ConversationPartner;
	
	UPROPERTY(BlueprintReadOnly,Category="Auto Generated Choice Data") // auto +
	FName ChoiceID1;
	
	UPROPERTY(BlueprintReadOnly,Category="Auto Generated Choice Data") // auto
	TArray<FName> RelatedNPC_Dialogues;

	UPROPERTY(BlueprintReadOnly,Category="Auto Generated Choice Data") // auto
	TArray<FName> RelatedNPC_Choices;

	
};

USTRUCT(BlueprintType)
struct FChoice2
{
	GENERATED_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ChoiceText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EffectsMood = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer RelatedGlobalEvents;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer EventsToTrigger;

	UPROPERTY(BlueprintReadOnly,Category="Auto Generated Choice Data") // auto
	bool EndOfDialogue = false;

	UPROPERTY(BlueprintReadOnly,Category="Auto Generated Choice Data") // auto
	EConversationPartner ConversationPartner;
	
	UPROPERTY(BlueprintReadOnly,Category="Auto Generated Choice Data") // auto +
	FName ChoiceID2;
	
	UPROPERTY(BlueprintReadOnly,Category="Auto Generated Choice Data") // auto
	TArray<FName> RelatedNPC_Dialogues;

	UPROPERTY(BlueprintReadOnly,Category="Auto Generated Choice Data") // auto
	TArray<FName> RelatedNPC_Choices;
};

USTRUCT(BlueprintType)
struct FChoice3
{
	GENERATED_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ChoiceText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EffectsMood = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer RelatedGlobalEvents;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer EventsToTrigger;

	UPROPERTY(BlueprintReadOnly,Category="Auto Generated Choice Data") // auto
	bool EndOfDialogue = false;

	UPROPERTY(BlueprintReadOnly,Category="Auto Generated Choice Data") // auto
	EConversationPartner ConversationPartner;
	
	UPROPERTY(BlueprintReadOnly,Category="Auto Generated Choice Data") // auto +
	FName ChoiceID3;
	
	UPROPERTY(BlueprintReadOnly,Category="Auto Generated Choice Data") // auto
	TArray<FName> RelatedNPC_Dialogues;

	UPROPERTY(BlueprintReadOnly,Category="Auto Generated Choice Data") // auto
	TArray<FName> RelatedNPC_Choices;
};
 
USTRUCT(BlueprintType)
struct FMainCharacterChoices : public FTableRowBase
{
	GENERATED_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FChoice1 Choice1;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FChoice2 Choice2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FChoice3 Choice3;
};


