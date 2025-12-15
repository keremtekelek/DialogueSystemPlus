

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerCPP.generated.h"

class USubsystem_Dialogue;
class UWidget_Dialogue;
class UWidget_Debug;
/**
 * 
 */
UCLASS()
class DIALOGUESYSTEMPLUS_API APlayerControllerCPP : public APlayerController
{
	GENERATED_BODY()

public:

	APlayerControllerCPP();

protected:

	
	virtual void BeginPlay() override;

public:

	UPROPERTY()
	USubsystem_Dialogue* DialogueSubsystem;

	UPROPERTY(EditAnywhere)
	UWidget_Dialogue* DialogueWidgetRef;

	UPROPERTY()
	TSubclassOf<UWidget_Dialogue> DialogueWidgetClass;

	UPROPERTY(EditAnywhere)
	UWidget_Debug* DebugWidgetRef;

	UPROPERTY()
	TSubclassOf<UWidget_Debug> DebugWidgetClass;


public:

	UFUNCTION()
	void GettingVariables();

	UFUNCTION()
	void GivingVariables();
	
};
