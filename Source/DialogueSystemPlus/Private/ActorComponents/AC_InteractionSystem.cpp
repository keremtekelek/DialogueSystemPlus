#include "ActorComponents/AC_InteractionSystem.h"

#include "Components/WidgetComponent.h"
#include "Interfaces/Interface_MainCharacter.h"


UAC_InteractionSystem::UAC_InteractionSystem()
{
	
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.5f;
	
}



void UAC_InteractionSystem::BeginPlay()
{
	Super::BeginPlay();

	GettingVariables();
}



void UAC_InteractionSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (IsMainCharacterInDialogueCollision)
	{
		FString moodString = FString::FromInt(AC_DialogueSystem->MoodValue);
		FText mood = FText::FromString(moodString);
		
		AC_DialogueSystem->WBP_MoodMeter->ShowMoodValue(true, mood);
	}
	else
	{
		AC_DialogueSystem->WBP_MoodMeter->ShowMoodValue(false, FText());
	}
}


//Market Collision's BeginOverlap event
void UAC_InteractionSystem::OnTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString moodString = FString::FromInt(AC_DialogueSystem->MoodValue);
	FText mood = FText::FromString(moodString);
	
	DialogueSubsystem->AC_InteractionSystem = this;
	
	if (OtherActor->GetClass()->ImplementsInterface(UInterface_MainCharacter::StaticClass()))
	{
		IsMainCharacterInDialogueCollision = true;
	}
}

//Market Collision's EndOverlap event
void UAC_InteractionSystem::OnTriggerEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	DialogueSubsystem->AC_InteractionSystem = nullptr;

	if (OtherActor->GetClass()->ImplementsInterface(UInterface_MainCharacter::StaticClass()))
	{
		IsMainCharacterInDialogueCollision = false;
	}
}

//Getting Useful Variables!
void UAC_InteractionSystem::GettingVariables()
{
	// Getting This Actor Component's Owner
	AActor* Owner = GetOwner();

	//Binding MarketCollision's Begin and End Overlap's
	if (MarketCollision)
	{
		MarketCollision->OnActorBeginOverlap.AddDynamic(this, &UAC_InteractionSystem::OnTriggerBeginOverlap);
		MarketCollision->OnActorEndOverlap.AddDynamic(this, &UAC_InteractionSystem::OnTriggerEndOverlap);
	}

	//Getting Dialogue Subsystem
	if (UWorld* World = GetWorld())
	{
		if (UGameInstance* GI = World->GetGameInstance())
		{
			DialogueSubsystem = GI->GetSubsystem<USubsystem_Dialogue>();
		}
	}

	//Getting AC_DialogueSystem from Owner
	if (IsValid(Owner) && Owner->GetClass()->ImplementsInterface(UInterface_NPC_Mood::StaticClass()))
	{
		AC_DialogueSystem = IInterface_NPC_Mood::Execute_GetDialogueSystemComponent(Owner);
	}
}


