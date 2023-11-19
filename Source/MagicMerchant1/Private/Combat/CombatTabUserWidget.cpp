// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/CombatTabUserWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h" 

void UCombatTabUserWidget::NativeConstruct()
{
	if (Attack1Button && Item1Button && BackButton)
	{
		//delegate calls, function will be called from click
		Attack1Button->OnClicked.AddDynamic(this, &UCombatTabUserWidget::Attack1ButtonOnClicked);
		Item1Button->OnClicked.AddDynamic(this, &UCombatTabUserWidget::Item1ButtonOnClicked);
		BackButton->OnClicked.AddDynamic(this, &UCombatTabUserWidget::BackButtonOnClicked);
	}

	GamemodeRef = Cast<AMagicMerchant1GameModeBase>(GetWorld()->GetAuthGameMode());
	PlayerRef = Cast<ABetterPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

}

//When button is pressed it changes text label to 17
void UCombatTabUserWidget::Attack1ButtonOnClicked()
{
	//enenmy attacked
	TextLabel->SetText(FText::FromString("EnemyAttacked"));
	PlayerRef->AttackEnemy();
	
}

void UCombatTabUserWidget::Item1ButtonOnClicked()
{
	TextLabel->SetText(FText::FromString("Item1Pressed"));
	//item consumed
}

void UCombatTabUserWidget::BackButtonOnClicked()
{
	TextLabel->SetText(FText::FromString("BackPressed"));
	//BackButton pressed
	GamemodeRef->RemoveCombatWidget();
	//Display main ui again
	GamemodeRef->AddMainUIWidget();

}
