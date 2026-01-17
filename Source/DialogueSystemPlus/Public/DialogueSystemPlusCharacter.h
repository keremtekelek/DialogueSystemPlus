

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Interfaces/Interface_MainCharacter.h"
#include "Interfaces/Interface_Interaction.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "DialogueSystemPlusCharacter.generated.h"


class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class USubsystem_Dialogue;
class USubsystem_EventManager;


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ADialogueSystemPlusCharacter : public ACharacter, public IInterface_MainCharacter, public IInterface_Interaction
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SkipDialogueAction;
	
	

	UPROPERTY()
	bool IsCharacterSprinting = false;

	//

	

	
public:
	ADialogueSystemPlusCharacter();
	

protected:

	// Input Functions!
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void SprintStart(const FInputActionValue& Value);
	void SprintEnd(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void SkipDialogue(const FInputActionValue& Value);

			

protected:

	// Overriding Engine Functions!
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Subsystems")
	USubsystem_EventManager* Subsystem_EventManager;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Data")
	TMap<FName, int32> DSM_MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Data")
	UDataTable* DataTable_MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Data")
	UDataTable* DataTable_MainCharacterDialogue;

	UPROPERTY()
	USubsystem_Dialogue* DialogueSubsystem;

	

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "Event Manager Functions")
	void HandleGameEvent(FGameplayTag EventTag);

	UFUNCTION()
	void EventReceived(FGameplayTag EventTag);
	
	
};

