#include "UI/Widget_StartMenu.h"
#include "PlayerController/PlayerControllerCPP.h"

void UWidget_StartMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Cb_ChoseLanguage)
	{
		Cb_ChoseLanguage->ClearOptions();

		Cb_ChoseLanguage->AddOption(TEXT("English"));
		Cb_ChoseLanguage->AddOption(TEXT("Turkish"));

		Cb_ChoseLanguage->SetSelectedOption(TEXT("English"));
	}
	
	if (StartButton)
	{
		//StartButton->OnClicked.RemoveDynamic(this, &UWidget_StartMenu::OnStartClicked);
		StartButton->OnClicked.AddDynamic(this, &UWidget_StartMenu::OnStartClicked);
	}

	if (QuitButton)
	{
		//QuitButton->OnClicked.RemoveDynamic(this, &UWidget_StartMenu::OnQuitClicked);
		QuitButton->OnClicked.AddDynamic(this, &UWidget_StartMenu::OnQuitClicked);
	}
}

void UWidget_StartMenu::OnStartClicked()
{
	if (LevelToLoad != NAME_None)
	{
		UGameplayStatics::OpenLevel(this, LevelToLoad);
		UE_LOG(LogTemp, Log, TEXT("Loading Level: %s"), *LevelToLoad.ToString());
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


