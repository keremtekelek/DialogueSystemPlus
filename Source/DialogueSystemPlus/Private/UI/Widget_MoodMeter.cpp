#include "UI/Widget_MoodMeter.h"

void UWidget_MoodMeter::NativeConstruct()
{
	this->SetVisibility(ESlateVisibility::Visible);
	ShowMoodValue(false, FText());
}

void UWidget_MoodMeter::NativePreConstruct()
{
	
}

void UWidget_MoodMeter::ShowMoodValue(bool ShouldShowMoodValue, FText TextToDisplay)
{
	if (ShouldShowMoodValue)
	{
		MoodValue->SetVisibility(ESlateVisibility::Visible);

		MoodValue->SetText(TextToDisplay);
	}
	else
	{
		MoodValue->SetVisibility(ESlateVisibility::Hidden);
		MoodValue->SetText(FText());
	}
}


