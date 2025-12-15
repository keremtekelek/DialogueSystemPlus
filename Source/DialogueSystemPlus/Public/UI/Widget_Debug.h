

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Widget_Debug.generated.h"


class USubsystem_Dialogue;
/**
 * 
 */
UCLASS()
class DIALOGUESYSTEMPLUS_API UWidget_Debug : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Debug_Text;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* Canvas;

	UPROPERTY(meta = (BindWidget))
	UBorder* DebugBorder;


	//Timers
	FTimerHandle UpdateTimerHandle;

	UPROPERTY()
	USubsystem_Dialogue* DialogueSubsystem;
public:

	UFUNCTION()
	void UpdateDebugData();

	
	
	
};


