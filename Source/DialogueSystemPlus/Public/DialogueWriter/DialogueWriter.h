

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
#include "DialogueWriter.generated.h"

class UBlueprint;
class NPC_DialogueNode;
class MainCharacterChoices_Node;

UENUM(BlueprintType)
enum class EThreeChoices : uint8
{
	Choice1 UMETA(DisplayName = "Choice 1"),
	Choice2 UMETA(DisplayName = "Choice 2"),
	Choice3 UMETA(DisplayName = "Choice 3")
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class DIALOGUESYSTEMPLUS_API UDialogueWriter : public UObject
{
	GENERATED_BODY()

public:

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


public:
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Dialogue Tools")
	void GenerateDialogueData();

protected:
	
	virtual void PostInitProperties() override;
	
private:
	
#if WITH_EDITOR
	
	void OnBlueprintCompiled(UBlueprint* InBlueprint);
#endif
	
};


