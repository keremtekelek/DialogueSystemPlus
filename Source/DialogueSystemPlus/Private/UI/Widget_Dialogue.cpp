#include "UI/Widget_Dialogue.h"

void UWidget_Dialogue::NativeConstruct()
{
	Super::NativeConstruct();

	CloseDialogue();
	CloseChoices();
}

void UWidget_Dialogue::NativePreConstruct()
{
	
}

// Widget Functions

void UWidget_Dialogue::ShowDialogue(FText DialogueToDisplay)
{
	DialogueText->SetVisibility(ESlateVisibility::Visible);
	DialogueText->SetText(DialogueToDisplay);
}

void UWidget_Dialogue::CloseDialogue()
{
	DialogueText->SetVisibility(ESlateVisibility::Hidden);
	DialogueText->SetText(FText());
}

void UWidget_Dialogue::ShowChoices(FText Choice1_Text, FText Choice2_Text, FText Choice3_Text)
{
	Choice1->SetVisibility(ESlateVisibility::Visible);
	Choice2->SetVisibility(ESlateVisibility::Visible);
	Choice3->SetVisibility(ESlateVisibility::Visible);

	Choice_1_text->SetVisibility(ESlateVisibility::Visible);
	Choice_2_text->SetVisibility(ESlateVisibility::Visible);
	Choice_3_text->SetVisibility(ESlateVisibility::Visible);

	Choice_1_text->SetText(Choice1_Text);
	Choice_2_text->SetText(Choice2_Text);
	Choice_3_text->SetText(Choice3_Text);
}

void UWidget_Dialogue::CloseChoices()
{
	Choice1->SetVisibility(ESlateVisibility::Hidden);
	Choice2->SetVisibility(ESlateVisibility::Hidden);
	Choice3->SetVisibility(ESlateVisibility::Hidden);

	Choice_1_text->SetVisibility(ESlateVisibility::Hidden);
	Choice_2_text->SetVisibility(ESlateVisibility::Hidden);
	Choice_3_text->SetVisibility(ESlateVisibility::Hidden);

	Choice_1_text->SetText(FText());
	Choice_2_text->SetText(FText());
	Choice_3_text->SetText(FText());
}
