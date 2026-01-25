#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"       
#include "Kismet/KismetSystemLibrary.h"
#include "Widget_StartMenu.generated.h"

class APlayerControllerCPP;
/**
 * 
 */
UCLASS()
class DIALOGUESYSTEMPLUS_API UWidget_StartMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	// Widget Componenets
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* Canvas;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox;
	
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton; 
	
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton; 
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StartText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuitText;
	
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Cb_ChoseLanguage;
	
	UPROPERTY(meta = (BindWidget))
	UImage* MenuBackground;
	
	//
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Settings")
	FName LevelToLoad = FName("ThirdPersonMap");
	
public:
	
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnStartClicked();

	UFUNCTION()
	void OnQuitClicked();
	
};
