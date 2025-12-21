#pragma once

#include "CoreMinimal.h"
#include "GlobalEnums.generated.h"

UENUM(BlueprintType)
enum class ENPCMood : uint8
{
	Neutral        UMETA(DisplayName = "Neutral"),    
	Happy	       UMETA(DisplayName = "Happy"),   
	NotHappy	   UMETA(DisplayName = "Not Happy"),
	DoesntMatter   UMETA(DisplayName = "Doesn't Matter") 
};

UENUM(BlueprintType)
enum class EConversationPartner : uint8
{
	DoesntMatter        UMETA(DisplayName = "DoesntMatter"),    
	AppleSeller	        UMETA(DisplayName = "AppleSeller"),   
	Butcher				UMETA(DisplayName = "Butcher"),
	Baker				UMETA(DisplayName = "Baker"),
	LemonSeller			UMETA(DisplayName = "LemonSeller"),
	PotatoSeller		UMETA(DisplayName = "PotatoSeller")
};

UENUM(BlueprintType)
enum class EChosenOption : uint8
{
	None        UMETA(DisplayName = "None"),    
	Choice1	    UMETA(DisplayName = "Choice1"),   
	Choice2		UMETA(DisplayName = "Choice2"),
	Choice3		UMETA(DisplayName = "Choice3"),
};

USTRUCT(BlueprintType)
struct FDialogueFlow
{
	GENERATED_BODY()
	
};