

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UI/Widget_MoodMeter.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "Enums/GlobalEnums.h"
#include "AC_DialogueSystem.generated.h"

class IInterface_NPC_Mood;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIALOGUESYSTEMPLUS_API UAC_DialogueSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UAC_DialogueSystem();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UWidget_MoodMeter* WBP_MoodMeter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	TMap<FName, int32> DSM_NPC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	int MoodValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Data")
	UDataTable* DataTable_NPC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	AActor* Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	ENPCMood NPC_Mood;

public:

	UFUNCTION()
	void GettingStaticVariables();

	UFUNCTION()
	void GettingDynamicVariables();

	UFUNCTION(BlueprintCallable)
	void AddMoodValue(int MoodValueToAdd);
		
};
