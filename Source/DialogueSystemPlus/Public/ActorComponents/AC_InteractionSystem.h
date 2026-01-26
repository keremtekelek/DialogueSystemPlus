

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerBox.h"
#include "Subsystems/Subsystem_Dialogue.h"
#include "ActorComponents/AC_DialogueSystem.h"
#include "Interfaces/Interface_NPC_Mood.h"
#include "Components/BillboardComponent.h"
#include "Engine/GameInstance.h" 
#include "AC_InteractionSystem.generated.h"


UENUM(BlueprintType)
enum class EBillboardType : uint8
{
	Pointer				UMETA(DisplayName = "Pointer"),    
	FloatingCircle	    UMETA(DisplayName = "FloatingCircle")   
	  
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIALOGUESYSTEMPLUS_API UAC_InteractionSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UAC_InteractionSystem();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collisions")
	ATriggerBox* MarketCollision;

	UPROPERTY()
	USubsystem_Dialogue* DialogueSubsystem;

	UPROPERTY(VisibleAnywhere)
	UAC_DialogueSystem* AC_DialogueSystem;

	UPROPERTY(VisibleAnywhere)
	bool IsMainCharacterInDialogueCollision;
	
	UPROPERTY()
	UBillboardComponent* PointerBillboard;

	UPROPERTY()
	UBillboardComponent* FloatingCircleBillboard;

public:

	// Market Collision's Begin and End Overlaps
	UFUNCTION()
	void OnTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
    
	UFUNCTION()
	void OnTriggerEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	// Function for getting useful variables!
	UFUNCTION()
	void GettingVariables();
	
	UFUNCTION()
	void OpenOrCloseBillboards(bool OpenOrCloseValue, EBillboardType WhichBillboard);

	
};
