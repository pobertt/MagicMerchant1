// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/CombatTabUserWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h" 

void UCombatTabUserWidget::NativeConstruct()
{
	for (int i = 0; i < 9; i++)
	{
		LockedButtons.Push(true);
		FirstClickArray.Push(true);
	}
	if (Attack1Button && Attack2Button && Attack3Button && Attack4Button && Item1Button && Item2Button && Item3Button && Item4Button && BackButton )
	{
		//delegate calls, function will be called from click
		
		//Attack Buttons

		Attack1Button->OnClicked.AddDynamic(this, &UCombatTabUserWidget::Attack1ButtonOnClicked);
		Attack2Button->OnClicked.AddDynamic(this, &UCombatTabUserWidget::Attack2ButtonOnClicked);
		Attack3Button->OnClicked.AddDynamic(this, &UCombatTabUserWidget::Attack3ButtonOnClicked);
		Attack4Button->OnClicked.AddDynamic(this, &UCombatTabUserWidget::Attack4ButtonOnClicked);

		//Item Buttons

		Item1Button->OnClicked.AddDynamic(this, &UCombatTabUserWidget::Item1ButtonOnClicked);
		Item2Button->OnClicked.AddDynamic(this, &UCombatTabUserWidget::Item2ButtonOnClicked);
		Item3Button->OnClicked.AddDynamic(this, &UCombatTabUserWidget::Item3ButtonOnClicked);
		Item4Button->OnClicked.AddDynamic(this, &UCombatTabUserWidget::Item4ButtonOnClicked);

		//Other Buttons 

		BackButton->OnClicked.AddDynamic(this, &UCombatTabUserWidget::BackButtonOnClicked);
	}

	GamemodeRef = Cast<AMagicMerchant1GameModeBase>(GetWorld()->GetAuthGameMode());
	PlayerRef = Cast<ABetterPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	PlayerRef->MakeEnemy();
	BaseEnemyRef = PlayerRef->BaseEnemyRef;
}

//Attack Button Functions 

void UCombatTabUserWidget::Attack1ButtonOnClicked()
{
	//old
	//enenmy attacked
	/*
	PlayerRef->AttackEnemy();
	TextLabel->SetText(FText::FromString("Attack 1 Used"));
	EnemyHPText->SetText(FText::AsNumber(BaseEnemyRef->CurrentHP));
	*/

	//Checks the cost of the button and whether the button is in the locked state
	if (PlayerRef->money < 0 && LockedButtons[0] == true)
	{
		//If true then say button is LOCKED
		TextLabel->SetText(FText::FromString("LOCKED"));
	}
	//Move onto this statemnent if player has enough money for the button 
	//(will always purchase if player has enough money anyways)
	else if (FirstClickArray[0] == true) {
		//Unlock's the button
		LockedButtons[0] = false;

		//Minusing the cost of the button from player money
		PlayerRef->money = PlayerRef->SubMoney(0);
		//Output text saying it is purchased
		TextLabel->SetText(FText::FromString("Purchased"));

		//Changing the original text to Attack 1 text
		Attack1TextBlock->SetText(FText::FromString("Attack 1"));
		//First Click has been consumed
		FirstClickArray[0] = false;
		return;
	}
	//If button is unlocked and the first click (purchase) is consumed 
	if (LockedButtons[0] == false && FirstClickArray[0] == false)
	{
		//Will run this code on click once button is purchased
		//Player Attack Enemy function being called 
		PlayerRef->AttackEnemy();

		//Output text
		TextLabel->SetText(FText::FromString("Attack 1 Used"));

		//output Enemy health 
		EnemyHPText->SetText(FText::AsNumber(BaseEnemyRef->CurrentHP));
	}
}

void UCombatTabUserWidget::Attack2ButtonOnClicked()
{
	if (PlayerRef->money < 1000 && LockedButtons[1] == true)
	{
		TextLabel->SetText(FText::FromString("LOCKED!"));
	}
	else if (FirstClickArray[1] == true) {
		LockedButtons[1] = false;

		PlayerRef->money = PlayerRef->SubMoney(1000);
		TextLabel->SetText(FText::FromString("Purchased"));

		Attack2TextBlock->SetText(FText::FromString("Attack 2"));
		FirstClickArray[1] = false;
		return;
	}

	if (LockedButtons[1] == false && FirstClickArray[1] == false)
	{
		PlayerRef->AttackEnemy();
		TextLabel->SetText(FText::FromString("Attack 2 Used"));
		EnemyHPText->SetText(FText::AsNumber(BaseEnemyRef->CurrentHP));
	}
}

void UCombatTabUserWidget::Attack3ButtonOnClicked()
{
	if (PlayerRef->money < 10000 && LockedButtons[2] == true)
	{
		TextLabel->SetText(FText::FromString("LOCKED!!"));
	}
	else if (FirstClickArray[2] == true) {
		LockedButtons[2] = false;

		PlayerRef->money = PlayerRef->SubMoney(10000);
		TextLabel->SetText(FText::FromString("Purchased"));

		Attack3TextBlock->SetText(FText::FromString("Attack 3"));
		FirstClickArray[2] = false;
		return;
	}

	if (LockedButtons[2] == false && FirstClickArray[2] == false)
	{
		PlayerRef->AttackEnemy();
		TextLabel->SetText(FText::FromString("Attack 3 Used"));
		EnemyHPText->SetText(FText::AsNumber(BaseEnemyRef->CurrentHP));
	}
}

void UCombatTabUserWidget::Attack4ButtonOnClicked()
{
	if (PlayerRef->money < 100000 && LockedButtons[3] == true)
	{
		TextLabel->SetText(FText::FromString("LOCKED!!!"));
	}
	else if (FirstClickArray[3] == true) {
		LockedButtons[3] = false;

		PlayerRef->money = PlayerRef->SubMoney(100000);
		TextLabel->SetText(FText::FromString("Purchased"));

		Attack4TextBlock->SetText(FText::FromString("Attack 4"));
		FirstClickArray[3] = false;
		return;
	}

	if (LockedButtons[3] == false && FirstClickArray[3] == false)
	{
		PlayerRef->AttackEnemy();
		TextLabel->SetText(FText::FromString("Attack 4 Used"));
		EnemyHPText->SetText(FText::AsNumber(BaseEnemyRef->CurrentHP));
	}
}

//Item Button Functions

void UCombatTabUserWidget::Item1ButtonOnClicked()
{
	if (PlayerRef->money < 0 && LockedButtons[4] == true)
	{
		TextLabel->SetText(FText::FromString("LOCKED"));
	}
	else if (FirstClickArray[4] == true) {
		LockedButtons[4] = false;

		PlayerRef->money = PlayerRef->SubMoney(0);
		TextLabel->SetText(FText::FromString("Purchased"));

		Item1TextBlock->SetText(FText::FromString("Item 1"));
		FirstClickArray[4] = false;
		return;
	}

	if (LockedButtons[4] == false && FirstClickArray[4] == false)
	{
		TextLabel->SetText(FText::FromString("Item consumed"));
		//item consumed function goes here
	}
}

void UCombatTabUserWidget::Item2ButtonOnClicked()
{
	if (PlayerRef->money < 2000 && LockedButtons[5] == true)
	{
		TextLabel->SetText(FText::FromString("LOCKED!"));
	}
	else if (FirstClickArray[5] == true) {
		LockedButtons[5] = false;

		PlayerRef->money = PlayerRef->SubMoney(2000);
		TextLabel->SetText(FText::FromString("Purchased"));

		Item2TextBlock->SetText(FText::FromString("Item 2"));
		FirstClickArray[5] = false;
		return;
	}

	if (LockedButtons[5] == false && FirstClickArray[5] == false)
	{
		TextLabel->SetText(FText::FromString("Item consumed"));
		//item consumed function goes here
	}
}

void UCombatTabUserWidget::Item3ButtonOnClicked()
{
	if (PlayerRef->money < 0 && LockedButtons[6] == true)
	{
		TextLabel->SetText(FText::FromString("LOCKED!!"));
	}
	else if (FirstClickArray[6] == true) {
		LockedButtons[6] = false;

		PlayerRef->money = PlayerRef->SubMoney(20000);
		TextLabel->SetText(FText::FromString("Purchased"));

		Item3TextBlock->SetText(FText::FromString("Item 3"));
		FirstClickArray[6] = false;
		return;
	}

	if (LockedButtons[6] == false && FirstClickArray[6] == false)
	{
		TextLabel->SetText(FText::FromString("Item consumed"));
		//item consumed function goes here
	}
}

void UCombatTabUserWidget::Item4ButtonOnClicked()
{
	if (PlayerRef->money < 0 && LockedButtons[7] == true)
	{
		TextLabel->SetText(FText::FromString("LOCKED!!!"));
	}
	else if (FirstClickArray[7] == true) {
		LockedButtons[7] = false;

		PlayerRef->money = PlayerRef->SubMoney(20000);
		TextLabel->SetText(FText::FromString("Purchased"));

		Item4TextBlock->SetText(FText::FromString("Item 4"));
		FirstClickArray[7] = false;
		return;
	}

	if (LockedButtons[7] == false && FirstClickArray[7] == false)
	{
		TextLabel->SetText(FText::FromString("Item consumed"));
		//item consumed function goes here
	}
}

//Button Functions

void UCombatTabUserWidget::BackButtonOnClicked()
{
	TextLabel->SetText(FText::FromString("BackPressed"));
	//BackButton pressed
	GamemodeRef->RemoveCombatWidget();
	//Display main ui again
	GamemodeRef->AddMainUIWidget();

}