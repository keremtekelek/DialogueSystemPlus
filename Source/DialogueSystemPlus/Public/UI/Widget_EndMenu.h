#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "Widget_EndMenu.generated.h"

class APlayerControllerCPP;

UCLASS()
class DIALOGUESYSTEMPLUS_API UWidget_EndMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//Widget Components
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* Canvas;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TheEndText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuitText;
	
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	
	UPROPERTY(meta = (BindWidget))
	UImage* MenuBackground;
	//
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Settings")
	FName LevelToLoad = FName("ThirdPersonMap");
public:
	
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void QuitButtonClicked();
};
