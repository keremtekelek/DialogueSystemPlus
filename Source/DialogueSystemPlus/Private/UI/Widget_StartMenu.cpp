#include "UI/Widget_StartMenu.h"
#include "PlayerController/PlayerControllerCPP.h"

void UWidget_StartMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Button_Start)
	{
		Button_Start->OnClicked.AddDynamic(this, &UWidget_StartMenu::OnStartClicked);
	}

	if (Button_Quit)
	{
		Button_Quit->OnClicked.AddDynamic(this, &UWidget_StartMenu::OnQuitClicked);
	}
	
	if (Button_PreviousLanguage)
	{
		Button_PreviousLanguage->OnClicked.AddDynamic(this, &UWidget_StartMenu::PreviousLanguageButtonClicked);
	}
	
	if (Button_NextLanguage)
	{
		Button_NextLanguage->OnClicked.AddDynamic(this, &UWidget_StartMenu::NextLanguageButtonClicked);
	}
	
	
	CurrentLanguageText->SetText(FText::FromString(LanguageNames[0]));
	FInternationalization::Get().SetCurrentCulture(CultureCodes[0]);
}

void UWidget_StartMenu::OnStartClicked()
{
	if (LevelToLoad != NAME_None)
	{
		UGameplayStatics::OpenLevel(this, LevelToLoad);
		UE_LOG(LogTemp, Log, TEXT("Loading Level: %s"), *LevelToLoad.ToString());
		
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		APlayerControllerCPP* PlayerController = Cast<APlayerControllerCPP>(PC);
		
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;
		FSlateApplication::Get().SetAllUserFocusToGameViewport();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Level Name is empty!"));
	}
}

void UWidget_StartMenu::OnQuitClicked()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	APlayerControllerCPP* PlayerController = Cast<APlayerControllerCPP>(PC);
	
	if (PlayerController)
	{
		UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, false);
		UE_LOG(LogTemp, Log, TEXT("Quit Game Clicked!"));
	}
}


void UWidget_StartMenu::PreviousLanguageButtonClicked()
{
	if (CurrentLanguageIndex > 0)
	{
		CurrentLanguageIndex--;
		UpdateLanguage();
	}
	else if (CurrentLanguageIndex == 0)
	{
		//UpdateLanguage();
		//we do nothing
	}
}

void UWidget_StartMenu::NextLanguageButtonClicked()
{
	if (CurrentLanguageIndex == CultureCodes.Num() - 1)
	{
		//UpdateLanguage();
		// we do nothing
	}
	else
	{
		CurrentLanguageIndex++;
		UpdateLanguage();
	}
}

void UWidget_StartMenu::UpdateLanguage()
{
	CurrentLanguageText->SetText(FText::FromString(LanguageNames[CurrentLanguageIndex]));
	FInternationalization::Get().SetCurrentCulture(CultureCodes[CurrentLanguageIndex]);
	
	PlayAnimation(ChangeLanguageAnim,0.0f,1,EUMGSequencePlayMode::Forward, 1.0f);
}




