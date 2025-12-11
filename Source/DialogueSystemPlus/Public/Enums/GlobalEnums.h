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

USTRUCT(BlueprintType)
struct FDialogueFlow
{
	GENERATED_BODY()
	
};