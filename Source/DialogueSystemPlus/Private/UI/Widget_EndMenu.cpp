#include "UI/Widget_EndMenu.h"
#include "PlayerController/PlayerControllerCPP.h"

void UWidget_EndMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UWidget_EndMenu::QuitButtonClicked);
	}
}

void UWidget_EndMenu::QuitButtonClicked()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	APlayerControllerCPP* PlayerController = Cast<APlayerControllerCPP>(PC);
	
	if (PlayerController)
	{
		UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, false);
		UE_LOG(LogTemp, Log, TEXT("Quit Game Clicked!"));
	}
}
