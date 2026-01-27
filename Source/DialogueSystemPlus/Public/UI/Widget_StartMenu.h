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
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Settings")
	FName LevelToLoad = FName("ThirdPersonMap");
	
	UPROPERTY()
	TArray<FString> LanguageNames = {TEXT("Türkçe"), TEXT("English")};
	
	UPROPERTY()
	TArray<FString> CultureCodes = {TEXT("tr"), TEXT("en")};
	
	UPROPERTY()
	int CurrentLanguageIndex = 0;
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ChangeLanguageAnim;
	
public:
	
	virtual void NativeConstruct() override;
	
	//Button functions
	
	UFUNCTION()
	void OnStartClicked();

	UFUNCTION()
	void OnQuitClicked();
	
	UFUNCTION()
	void PreviousLanguageButtonClicked();
	
	UFUNCTION()
	void NextLanguageButtonClicked();
	
	UFUNCTION()
	void UpdateLanguage();
};
