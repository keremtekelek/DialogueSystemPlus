#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h" 
#include "Components/TextBlock.h"
#include "Widget_MoodMeter.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEMPLUS_API UWidget_MoodMeter : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
public:

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* Canvas;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MoodValue;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StaticText;

public:

	UFUNCTION(BlueprintCallable)
	void ShowMoodValue(bool ShouldShowMoodValue, FText TextToDisplay);
	
};
