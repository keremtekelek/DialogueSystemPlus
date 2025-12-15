#include "PlayerController/PlayerControllerCPP.h"
#include "Subsystems/Subsystem_Dialogue.h"
#include "UI/Widget_Dialogue.h"
#include "UI/Widget_Debug.h"


APlayerControllerCPP::APlayerControllerCPP()
{
	DialogueWidgetRef = nullptr;

	static ConstructorHelpers::FClassFinder<UWidget_Dialogue> WidgetBPClass(TEXT("/Game/01_MyContent/Blueprints/UI/WBP_Dialogue"));
	if (WidgetBPClass.Succeeded())
	{
		DialogueWidgetClass = WidgetBPClass.Class;
	}


	DebugWidgetRef = nullptr;

	static ConstructorHelpers::FClassFinder<UWidget_Debug> DebugClass(TEXT("/Game/01_MyContent/Blueprints/UI/WBP_Debug"));
	if (DebugClass.Succeeded())
	{
		DebugWidgetClass = DebugClass.Class;
	}
}



void APlayerControllerCPP::BeginPlay()
{
	Super::BeginPlay();

	GettingVariables();
	GivingVariables();
}


void APlayerControllerCPP::GettingVariables()
{
	if (UGameInstance* GI = GetGameInstance())
	{
		DialogueSubsystem = GI->GetSubsystem<USubsystem_Dialogue>();
	}
	
}

void APlayerControllerCPP::GivingVariables()
{
	if (DialogueSubsystem)
	{
		DialogueSubsystem->PlayerController = this;
	}


	if (DialogueWidgetClass)
	{
		DialogueWidgetRef = CreateWidget<UWidget_Dialogue>(GetWorld(), DialogueWidgetClass);

		if (DialogueWidgetRef)
		{
			DialogueWidgetRef->AddToViewport();

			if (DialogueSubsystem)
			{
				DialogueSubsystem->WBP_Dialogue = DialogueWidgetRef;
				GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green, FString("subsystem valid"));
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green, FString("subsystem NOT valid"));
			}
		}
	}


	if (DebugWidgetClass)
	{
		DebugWidgetRef = CreateWidget<UWidget_Debug>(GetWorld(), DebugWidgetClass);

		if (DebugWidgetRef)
		{
			DebugWidgetRef->AddToViewport();
		}
	}
}


