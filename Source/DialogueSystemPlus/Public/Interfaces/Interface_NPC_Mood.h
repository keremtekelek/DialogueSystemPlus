#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/GlobalEnums.h"
#include "Engine/DataTable.h"
#include "ActorComponents/AC_DialogueSystem.h"
#include "Interface_NPC_Mood.generated.h"



UINTERFACE(MinimalAPI)
class UInterface_NPC_Mood : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DIALOGUESYSTEMPLUS_API IInterface_NPC_Mood
{
	GENERATED_BODY()

	
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "NPC Mood")
	void AddMoodValue(int MoodValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "NPC Mood")
	int GetMoodValue();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "NPC Mood")
	ENPCMood GetMood();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "NPC Mood")
	class UWidgetComponent* GetMoodMeter();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "NPC Data")
	UAC_DialogueSystem* GetDialogueSystemComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "NPC Data")
	void GetDataTableAndScoreData(UDataTable*& NPC_DataTable, TMap<FName, int32>& DSM_NPCC);
	
};
