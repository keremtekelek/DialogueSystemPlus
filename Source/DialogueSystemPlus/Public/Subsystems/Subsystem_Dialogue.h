

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/Widget_MoodMeter.h"
#include "UI/Widget_Dialogue.h"
#include "ActorComponents/AC_DialogueSystem.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Enums/GlobalEnums.h"
#include "DialogueSystemPlusCharacter.h"
#include "Subsystem_Dialogue.generated.h"

class UAC_InteractionSystem;
/**
 * 
 */
UCLASS()
class DIALOGUESYSTEMPLUS_API USubsystem_Dialogue : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
public:

	UPROPERTY(EditAnywhere, Category = "Components")
	UAC_InteractionSystem* AC_InteractionSystem;

	UPROPERTY(EditAnywhere, Category = "Components")
	UAC_DialogueSystem* AC_DialogueSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	UWidget_MoodMeter* WBP_MoodMeter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue Widget")
	UWidget_Dialogue* WBP_Dialogue;

	UPROPERTY()
	TSubclassOf<UWidget_Dialogue> DialogueWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	UDataTable* DataTable_NPC;

	// DSM stands for "Dialogue Score Map".
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	TMap<FName, int32> DSM_NPC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	int MoodValue_NPC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	ENPCMood Mood_NPC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main Character Data")
	ADialogueSystemPlusCharacter* MainCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main Character Data")
	TMap<FName, int32> DSM_MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Character Data")
	UDataTable* DataTable_MainCharacter;

	
	
public:

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interacted();

	UFUNCTION(BlueprintCallable)
	void GettingVariables();
	
};
