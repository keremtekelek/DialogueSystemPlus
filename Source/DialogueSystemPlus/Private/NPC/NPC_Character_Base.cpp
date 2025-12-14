#include "NPC/NPC_Character_Base.h"


ANPC_Character_Base::ANPC_Character_Base()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Mood Meter Widget"));

	if (WidgetComp)
	{
		WidgetComp->SetupAttachment(GetMesh());
		WidgetComp->SetWidgetSpace(EWidgetSpace::World);
		WidgetComp->SetDrawSize(FVector2D(150, 150));
		WidgetComp->SetRelativeLocation(FVector(0, 10, 200));
		static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass{ TEXT("/Game/01_MyContent/Blueprints/UI/WBP_MoodMeter") };

		if (WidgetClass.Succeeded())
		{
			WidgetComp->SetWidgetClass((WidgetClass.Class));
		}
	}

	AC_DialogueSystem = CreateDefaultSubobject<UAC_DialogueSystem>(TEXT("DialogueSystem_Component"));
	AC_InteractionSystem = CreateDefaultSubobject<UAC_InteractionSystem>(TEXT("InteractionSystem_Component"));
	

}


void ANPC_Character_Base::BeginPlay()
{
	Super::BeginPlay();

	WidgetComp->InitWidget();
}


void ANPC_Character_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Interface_NPC_Mood's Functions

void ANPC_Character_Base::AddMoodValue_Implementation(int MoodValue)
{
	NPC_MoodValue = NPC_MoodValue + MoodValue;
}

int ANPC_Character_Base::GetMoodValue_Implementation()
{
	return NPC_MoodValue;
}

ENPCMood ANPC_Character_Base::GetMood_Implementation()
{
	if (0 <= NPC_MoodValue && NPC_MoodValue < 25)
	{
		return ENPCMood::NotHappy;
	}
	else if (25 <= NPC_MoodValue && NPC_MoodValue < 75)
	{
		return ENPCMood::Neutral;
	}
	else if (75 <= NPC_MoodValue && NPC_MoodValue <= 100)
	{
		return ENPCMood::Happy;
	}
	else
	{
		// Can be change
		return ENPCMood::DoesntMatter;
	}
}

UWidgetComponent* ANPC_Character_Base::GetMoodMeter_Implementation()
{
	if (IsValid(WidgetComp))
	{
		return WidgetComp;
	}
	else
	{
		return nullptr;
	}
}

UAC_DialogueSystem* ANPC_Character_Base::GetDialogueSystemComponent_Implementation()
{
	if (IsValid(AC_DialogueSystem))
	{
		return AC_DialogueSystem;
	}
	else
	{
		return nullptr;
	}
}

void ANPC_Character_Base::GetDataTableAndScoreData_Implementation(UDataTable*& NPC_DataTable, TMap<FName, int32>& DSM_NPCC)
{
	if (DataTable_NPC)
	{
		NPC_DataTable = DataTable_NPC;
		DSM_NPCC = DSM_NPC;
	}
	
}

EConversationPartner ANPC_Character_Base::GetInteractedCharacter_Implementation()
{
	if (CharacterName.ToString().ToLower() == FString("lemonseller"))
	{
		return EConversationPartner::LemonSeller;
	}

	else if (CharacterName.ToString().ToLower() == FString("appleseller"))
	{
		return EConversationPartner::AppleSeller;
	}

	else if (CharacterName.ToString().ToLower() == FString("butcher"))
	{
		return EConversationPartner::Butcher;
	}

	else if (CharacterName.ToString().ToLower() == FString("baker"))
	{
		return EConversationPartner::Baker;
	}

	else if (CharacterName.ToString().ToLower() == FString("potatoseller"))
	{
		return EConversationPartner::PotatoSeller;
	}
	else
	{
		return EConversationPartner::DoesntMatter;
	}
}


