#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Enums/GlobalEnums.h"
#include "Structs/MainCharacter/S_MainCharacterChoices.h"
#include "Structs/NPC/S_NPC_Dialogues.h"
#include "Engine/Blueprint.h"
#include "EdGraph/EdGraph.h"
#include "K2Node_CallFunction.h" 
#include "Engine/DataTable.h"
#include "FunctionLibrary_DialogueScanner.generated.h"

/**
 * 
 */

class UDialogueWriter;
UCLASS()
class DIALOGUESYSTEMPLUS_API UFunctionLibrary_DialogueScanner : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION()
	static void ScanAndExport(UDialogueWriter* DialogueWriter);
	
};
