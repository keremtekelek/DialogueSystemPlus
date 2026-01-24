#include "ActorComponents/AC_DialogueSystem.h"
#include "Interfaces/Interface_NPC_Mood.h"
#include "Components/WidgetComponent.h"


UAC_DialogueSystem::UAC_DialogueSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;     
	PrimaryComponentTick.TickInterval = 0.5f;
}



void UAC_DialogueSystem::BeginPlay()
{
	Super::BeginPlay();

	GettingStaticVariables();
}



void UAC_DialogueSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GettingDynamicVariables();
}

// Getting Useful Static Variables
void UAC_DialogueSystem::GettingStaticVariables()
{
	// Getting This Component's Owner
	Owner = GetOwner();

	
	if (IsValid(Owner) && Owner->GetClass()->ImplementsInterface(UInterface_NPC_Mood::StaticClass()))
	{
		//Getting WBP_MoodMeter from Owner
		UWidgetComponent* WidgetComp = IInterface_NPC_Mood::Execute_GetMoodMeter(Owner);
		if (WidgetComp)
		{
			WBP_MoodMeter = Cast<UWidget_MoodMeter>(WidgetComp->GetWidget());
		}

		//Getting Data Table and DSM(Dialogue Score Map) from owner
		IInterface_NPC_Mood::Execute_GetDataTableAndScoreData(Owner,DataTable_NPC, DSM_NPC);

		//Getting Owner NPC Name
		InteractedCharacter = IInterface_NPC_Mood::Execute_GetInteractedCharacter(Owner);
	}
	
	OriginalRotation = Owner->GetActorRotation();
}

// Getting Useful Dynamic Variables
void UAC_DialogueSystem::GettingDynamicVariables()
{
	if (IsValid(Owner) && Owner->GetClass()->ImplementsInterface(UInterface_NPC_Mood::StaticClass()))
	{
		// Getting Mood Value from Owner
		MoodValue = IInterface_NPC_Mood::Execute_GetMoodValue(Owner);
		NPC_Mood = IInterface_NPC_Mood::Execute_GetMood(Owner);
	}

	if (IsValid(Owner))
	{
		OwnerLocation = Owner->GetActorLocation();
		OwnerRotation = Owner->GetActorRotation();
	}
}

void UAC_DialogueSystem::AddMoodValue(int MoodValueToAdd)
{
	if (IsValid(Owner) && Owner->GetClass()->ImplementsInterface(UInterface_NPC_Mood::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Mood Value has been worked. Value is:%d"),MoodValueToAdd);
		IInterface_NPC_Mood::Execute_AddMoodValue(Owner, MoodValueToAdd);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Mood Value not worked. Value to add is:%d"),MoodValueToAdd);
	}
}

void UAC_DialogueSystem::TurnBackOriginalRotation()
{
	if (IsValid(Owner))
	{
		Owner->SetActorRotation(OriginalRotation);
	}
}

void UAC_DialogueSystem::SetNPC_TransformProperties(FVector SetLocation)
{
	if (IsValid(Owner))
	{
		Owner->SetActorLocation(SetLocation);
	}
}

void UAC_DialogueSystem::SetNPC_TransformProperties(FRotator SetRotation)
{
	if (IsValid(Owner))
	{
		Owner->SetActorRotation(SetRotation);
	}
}

