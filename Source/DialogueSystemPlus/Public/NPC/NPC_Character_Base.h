#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enums/GlobalEnums.h"
#include "Interfaces/Interface_NPC_Mood.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "ActorComponents/AC_InteractionSystem.h"
#include "ActorComponents/AC_DialogueSystem.h"
#include "NPC_Character_Base.generated.h"

UCLASS()
class DIALOGUESYSTEMPLUS_API ANPC_Character_Base : public ACharacter, public IInterface_NPC_Mood
{
	GENERATED_BODY()

public:
	
	ANPC_Character_Base();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	

public:

	// VARIABLES!!
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Mood")
	int NPC_MoodValue = 50;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Mood")
	ENPCMood ENPC_Mood;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* WidgetComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAC_DialogueSystem* AC_DialogueSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAC_InteractionSystem* AC_InteractionSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	TMap<FName, int32> DSM_NPC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Data")
	UDataTable* DataTable_NPC;

public:
	
	// Interface_NPC_Mood's Functions
	virtual void AddMoodValue_Implementation(int MoodValue) override;
	virtual int GetMoodValue_Implementation() override;
	virtual ENPCMood GetMood_Implementation() override;
	virtual UWidgetComponent* GetMoodMeter_Implementation() override;
	virtual UAC_DialogueSystem* GetDialogueSystemComponent_Implementation() override;
	virtual void GetDataTableAndScoreData_Implementation(UDataTable*& NPC_DataTable, TMap<FName, int32>& DSM_NPCC) override;

};
