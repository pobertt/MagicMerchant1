// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/CombatTabUserWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h" 

void UCombatTabUserWidget::NativeConstruct()
{
	if (Attack1Button)
	{
		Attack1Button->OnClicked.AddDynamic(this, &UCombatTabUserWidget::Attack1ButtonOnClicked);
	}
}

//When button is pressed it changes text label to 17
void UCombatTabUserWidget::Attack1ButtonOnClicked()
{

	TextLabel->SetText(FText::FromString("EnemyAttacks"));
}
