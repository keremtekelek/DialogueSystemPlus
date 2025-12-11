

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structs/MainCharacter/S_MainCharacterChoices.h"
#include "Structs/NPC/S_NPC_Dialogues.h"
#include "Enums/GlobalEnums.h"
#include "K2Node_CallFunction.h"
#include "EdGraph/EdGraph.h"
#include "EdGraphSchema_K2.h"
#include "Engine/DataTable.h"
#include "Sound/SoundBase.h"
#include "DataTableEditorUtils.h"
#include "DialogueWriter.generated.h"

class UBlueprint;
class UNPC_DialogueNode;
class UMainCharacterChoices_Node;



/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class DIALOGUESYSTEMPLUS_API UDialogueWriter : public UObject
{
	GENERATED_BODY()

public:

	//***Data Tables***
	UPROPERTY(EditDefaultsOnly, Category = "Data Tables")
	UDataTable* DT_AppleSeller;

	UPROPERTY(EditDefaultsOnly, Category = "Data Tables")
	UDataTable* DT_Butcher;

	UPROPERTY(EditDefaultsOnly, Category = "Data Tables")
	UDataTable* DT_Baker;

	UPROPERTY(EditDefaultsOnly, Category = "Data Tables")
	UDataTable* DT_LemonSeller;

	UPROPERTY(EditDefaultsOnly, Category = "Data Tables")
	UDataTable* DT_PotatoSeller;

	UPROPERTY(EditDefaultsOnly, Category = "Data Tables")
	UDataTable* DT_MainCharacter;

	UPROPERTY()
	TArray<UEdGraphNode*> VisitedNPC_Nodes;

	UPROPERTY()
	TArray<UEdGraphNode*> VisitedMC_Nodes;
	
	UPROPERTY()
	TArray<UNPC_DialogueNode*> RootNPC_Nodes;
	
	UPROPERTY()
	TSet<FName> ActiveIDs;
	

	


public:
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Dialogue Tools")
	void GenerateDialogueData();

	

	
	UFUNCTION(BlueprintCallable, Category = "Data Table Functions")
	void ClearDataTables();

	UFUNCTION(BlueprintCallable, Category = "Data Table Functions")
	void MarkDataTablesAsDirty();
	
	UFUNCTION(BlueprintCallable, Category = "Data Table Functions")
	void AddToDataTable(UEdGraphNode* NodeToAddDataTable);
	
	UFUNCTION(BlueprintCallable, Category = "Data Table Functions")
	void HandleAutomatedData(UEdGraphNode* HandledNode);
	
	UFUNCTION(BlueprintCallable, Category = "Data Table Functions")
	void CleanGhostNodesFromTables();
	
	

protected:
	
	virtual void PostInitProperties() override;
	
private:
	
#if WITH_EDITOR
	
	void OnBlueprintCompiled(UBlueprint* InBlueprint);
#endif
	
};


