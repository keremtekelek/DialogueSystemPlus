#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Internationalization/Internationalization.h"
#include "Internationalization/Culture.h"
#include "Subsystem_Localization.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLocalizationChanged, FString, NewLanguageName);

UCLASS()
class DIALOGUESYSTEMPLUS_API USubsystem_Localization : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

public:
	
	UPROPERTY(VisibleAnywhere)
	TArray<FString> LanguageNames = {TEXT("Türkçe"), TEXT("English")};
	
	UPROPERTY(VisibleAnywhere)
	TArray<FString> CultureCodes = {TEXT("tr"), TEXT("en")};
	
	UPROPERTY(BlueprintAssignable, Category = "Localization")
	FLocalizationChanged LocalizationChanged;
	
private:
	
	UPROPERTY()
	int CurrentLanguageIndex = 0;
	
public:
	
	UFUNCTION(Category = "Widget Functions")
	void PreviousLanguageButtonClicked();
	
	UFUNCTION(Category = "Widget Functions")
	void NextLanguageButtonClicked();
	
	UFUNCTION(BlueprintPure, Category = "Localization Functions")
	FString GetCurrentLanguageName() const;
	
	UFUNCTION(Category = "Localization Functions")
	void SetDefaultLanguage(FString EnterCultureCode);
	
protected:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
private:
	
	UFUNCTION(Category = "Localization Functions")
	void UpdateLanguage();
	
};
