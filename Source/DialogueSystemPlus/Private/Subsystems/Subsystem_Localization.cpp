#include "Subsystems/Subsystem_Localization.h"


void USubsystem_Localization::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	SetDefaultLanguage("en");
}


void USubsystem_Localization::PreviousLanguageButtonClicked()
{
	if (CurrentLanguageIndex > 0)
	{
		CurrentLanguageIndex--;
		UpdateLanguage();
	}
}

void USubsystem_Localization::NextLanguageButtonClicked()
{
	if (!CurrentLanguageIndex == CultureCodes.Num() - 1)
	{
		CurrentLanguageIndex++;
		UpdateLanguage();
	}
}

FString USubsystem_Localization::GetCurrentLanguageName() const
{
	if(LanguageNames.IsValidIndex(CurrentLanguageIndex))
	{
		return LanguageNames[CurrentLanguageIndex];
	}
	
	return TEXT("Unknown");
}


void USubsystem_Localization::UpdateLanguage()
{
	FInternationalization::Get().SetCurrentCulture(CultureCodes[CurrentLanguageIndex]);
	
	if (LocalizationChanged.IsBound())
	{
		LocalizationChanged.Broadcast(LanguageNames[CurrentLanguageIndex]);
	}
}

void USubsystem_Localization::SetDefaultLanguage(FString EnterCultureCode)
{
	for(int i=0; i<CultureCodes.Num(); i++)
	{
		if(EnterCultureCode == CultureCodes[i])
		{
			FString CodeToMove = CultureCodes[i];
			CultureCodes.RemoveAt(i);
			CultureCodes.Insert(CodeToMove, 0);
			
			FString LanguageNameToMove = LanguageNames[i];
			LanguageNames.RemoveAt(i);
			LanguageNames.Insert(LanguageNameToMove, 0);
			
			CurrentLanguageIndex = 0;
			UpdateLanguage();
			
			break;
		}
	}
}
