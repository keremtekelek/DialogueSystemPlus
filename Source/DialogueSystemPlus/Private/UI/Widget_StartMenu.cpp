#include "UI/Widget_StartMenu.h"
#include "PlayerController/PlayerControllerCPP.h"
#include "Subsystems/Subsystem_Localization.h"

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
	
	UGameInstance* GI = GetGameInstance();
	if (GI)
	{
		Localization_Subsystem = GI->GetSubsystem<USubsystem_Localization>();
		
		if (Localization_Subsystem)
		{
			Localization_Subsystem->LocalizationChanged.AddDynamic(this, &UWidget_StartMenu::LanguageChangedHandler);
			
			CurrentLanguageText->SetText(FText::FromString(Localization_Subsystem->GetCurrentLanguageName()));
		}
	}
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
	Localization_Subsystem->PreviousLanguageButtonClicked();
}

void UWidget_StartMenu::NextLanguageButtonClicked()
{
	Localization_Subsystem->NextLanguageButtonClicked();
}

void UWidget_StartMenu::LanguageChangedHandler(FString NewLanguageName)
{
	if (!(NewLanguageName == "Unknown"))
	{
		CurrentLanguageText->SetText(FText::FromString(NewLanguageName));
	}
	
	PlayAnimation(ChangeLanguageAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
}





