#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"       
#include "Kismet/KismetSystemLibrary.h"
#include "Internationalization/Internationalization.h"
#include "Internationalization/Culture.h"
#include "Animation/WidgetAnimation.h"
#include "Widget_StartMenu.generated.h"

class APlayerControllerCPP;
class USubsystem_Localization;

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
	UButton* Button_Start; 
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Quit; 
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StartText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuitText;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_PreviousLanguage;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_NextLanguage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentLanguageText;
	
	UPROPERTY(meta = (BindWidget))
	UImage* MenuBackground;
	
	// Other Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Settings")
	FName LevelToLoad = FName("ThirdPersonMap");
	
	UPROPERTY()
	USubsystem_Localization* Localization_Subsystem;
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ChangeLanguageAnim;
	
	
protected:
	
	virtual void NativeConstruct() override;
	
public:
	
	UFUNCTION(Category = "Button Functions")
	void OnStartClicked();

	UFUNCTION(Category = "Button Functions")
	void OnQuitClicked();
	
	UFUNCTION(Category = "Button Functions")
	void PreviousLanguageButtonClicked();
	
	UFUNCTION(Category = "Button Functions")
	void NextLanguageButtonClicked();
	
	UFUNCTION()
	void LanguageChangedHandler(FString NewLanguageName);
};
