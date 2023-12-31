// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/CombatTabUserWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h" 

void UCombatTabUserWidget::NativeConstruct()
{
	if (Attack1Button && Attack2Button && Attack3Button && Attack4Button && Item1Button && Item2Button && Item3Button && Item4Button && IdleButton )
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

		IdleButton->OnClicked.AddDynamic(this, &UCombatTabUserWidget::IdleButtonOnClicked);
	}



	PlayerRef = Cast<ABetterPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	GameInstanceRef = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

	PlayerRef->MakeEnemy();
	BaseEnemyRef = PlayerRef->BaseEnemyRef;

	UpgradeProperties.Init(FUpgradeProperties(), 4);
	UpgradeProperties[0] = FUpgradeProperties(10, 50.f, 25);
}

//Attack Button Functions 

void UCombatTabUserWidget::AttackFunction(int Cost, int LockedButtonsIndex, int FirstClickArrayIndex, int Dmg, FString AttackUsed, float MPCost, FString AttackType)
{
	//Checks the cost of the button and whether the button is in the locked state
	if (PlayerRef->money < Cost && GameInstanceRef->LockedButtons[LockedButtonsIndex] == true)
	{
		//If true then say button is LOCKED
		TextLabel->SetText(FText::FromString("LOCKED"));
	}
	//Move onto this statemnent if player has enough money for the button 
	//(will always purchase if player has enough money anyways)
	else if (GameInstanceRef->FirstClickArray[FirstClickArrayIndex] == true) {

		//Unlock's the button
		GameInstanceRef->LockedButtons[LockedButtonsIndex] = false;

		//Minusing the cost of the button from player money
		PlayerRef->money = PlayerRef->SubMoney(Cost);

		//Output text saying it is purchased
		TextLabel->SetText(FText::FromString("Purchased"));
		GameInstanceRef->ButtonText[FirstClickArrayIndex] = "Attack " + FString::FormatAsNumber(FirstClickArrayIndex + 1);

		//First Click has been consumed
		GameInstanceRef->FirstClickArray[FirstClickArrayIndex] = false;
		return;
	}

	//If button is unlocked and the first click (purchase) is consumed 
	//and if mana can afford it 
	if (GameInstanceRef->LockedButtons[LockedButtonsIndex] == false && GameInstanceRef->FirstClickArray[FirstClickArrayIndex] == false && PlayerRef->mp > MPCost)
	{
		//Checking if HP is greater than 0
		if (BaseEnemyRef->CurrentHP > 0)
		{
			//If greater then deal dmg and print text
			PlayerRef->AttackEnemy(Dmg, MPCost, AttackType);
			TextLabel->SetText(FText::FromString(AttackUsed));
		}
		else if (BaseEnemyRef->CurrentHP == 0)
		{
			TextLabel->SetText(FText::FromString("Enemy Killed"));
		}
	}
}

void UCombatTabUserWidget::ItemFunction(int Cost, int LockedButtonsIndex, int FirstClickArrayIndex, FString ItemUsed, int Damage, float MPCost, int ItemCost, int ItemIndex)
{
	if (PlayerRef->money < Cost && GameInstanceRef->LockedButtons[LockedButtonsIndex] == true)
	{
		TextLabel->SetText(FText::FromString("LOCKED"));
	}
	else if (GameInstanceRef->FirstClickArray[FirstClickArrayIndex] == true) {
		GameInstanceRef->LockedButtons[LockedButtonsIndex] = false;

		PlayerRef->money = PlayerRef->SubMoney(Cost);
		TextLabel->SetText(FText::FromString("Purchased"));

		GameInstanceRef->ButtonText[FirstClickArrayIndex] = "Item " + FString::FormatAsNumber(FirstClickArrayIndex - 3);

		GameInstanceRef->FirstClickArray[FirstClickArrayIndex] = false;
		return;
	}
	if (GameInstanceRef->LockedButtons[LockedButtonsIndex] == false && GameInstanceRef->FirstClickArray[FirstClickArrayIndex] == false)
	{
		TextLabel->SetText(FText::FromString(ItemUsed));
		//item consumed function goes here

		UpgradeProperties[ItemIndex] = ItemUpgrade(Damage, MPCost, ItemCost, ItemIndex);

	}
}

void UCombatTabUserWidget::Attack1ButtonOnClicked()
{
	//If the button can be clicked
	if (bCanClick == true)
	{
		//The button now can't be clicked until Button Timer Reset is called
		bCanClick = false;

		//Calling the Attack Function
		AttackFunction(0, 0, 0, UpgradeProperties[0].Damage,"Normal Attack Used", UpgradeProperties[0].MPCost, "Normal");
		
		//If the button is unlocked 
		if (GameInstanceRef->LockedButtons[0] == false)
		{
			//Set the all button text to on cooldown
			CooldownText();
			// GameInstanceRef->ButtonText[0] = "Cooldown";

			//This all seems redundant currently but it helped me understand delegates 
			//Seems redudant as if i am setting them all to go cooldown and then setting them back to their original text, 
			//whats the point of the specific timer?

			FTimerDelegate Delegate;

			//Assigning the function to the timer and passing in parameters 
			Delegate.BindUFunction(this, "ChangeButtonText", Attack1TextBlock, 1);

			//Set this specific timer back to the original text
			GetWorld()->GetTimerManager().SetTimer(
				ButtonPressTimerHandle,
				Delegate,
				//&UCombatTabUserWidget::ButtonTimerReset,
				1.0f,
				false);

			//setting them all back to their original text
			GetWorld()->GetTimerManager().SetTimer(
				ButtonPressTimerHandle,
				this,
				&UCombatTabUserWidget::ButtonTimerReset,
				1.0f,
				false);

		}
	}
}

void UCombatTabUserWidget::Attack2ButtonOnClicked()
{
	if (Idle == false)
	{
		if (bCanClick == true)
		{
			bCanClick = false;
			AttackFunction(2500, 1, 1, UpgradeProperties[1].Damage, "Fire Attack Used", UpgradeProperties[1].MPCost, "Fire");

			if (GameInstanceRef->LockedButtons[1] == false)
			{
				CooldownText();

				FTimerDelegate Delegate;
				Delegate.BindUFunction(this, "ChangeButtonText", Attack2TextBlock, 2);

				GetWorld()->GetTimerManager().SetTimer(
					ButtonPressTimerHandle,
					Delegate,
					1.0f,
					false);

				GetWorld()->GetTimerManager().SetTimer(
					ButtonPressTimerHandle,
					this,
					&UCombatTabUserWidget::ButtonTimerReset,
					1.0f,
					false);
			}
		}
	}
}

void UCombatTabUserWidget::Attack3ButtonOnClicked()
{
	if (Idle == false)
	{
		if (bCanClick == true)
		{
			bCanClick = false;
			AttackFunction(2500, 2, 2, UpgradeProperties[2].Damage, "Grass Attack Used", UpgradeProperties[2].MPCost, "Grass");

			if (GameInstanceRef->LockedButtons[2] == false)
			{
				CooldownText();

				FTimerDelegate Delegate;
				Delegate.BindUFunction(this, "ChangeButtonText", Attack3TextBlock, 3);

				GetWorld()->GetTimerManager().SetTimer(
					ButtonPressTimerHandle,
					Delegate,
					1.0f,
					false);


				GetWorld()->GetTimerManager().SetTimer(
					ButtonPressTimerHandle,
					this,
					&UCombatTabUserWidget::ButtonTimerReset,
					1.0f,
					false);
			}
		}
	}
}

void UCombatTabUserWidget::Attack4ButtonOnClicked()
{
	if (Idle == false)
	{
		if (bCanClick == true)
		{
			bCanClick = false;
			AttackFunction(2500, 3, 3, UpgradeProperties[3].Damage, "Water Attack Used", UpgradeProperties[3].MPCost, "Water");

			if (GameInstanceRef->LockedButtons[3] == false)
			{
				CooldownText();

				FTimerDelegate Delegate;
				Delegate.BindUFunction(this, "ChangeButtonText", Attack4TextBlock, 4);

				GetWorld()->GetTimerManager().SetTimer(
					ButtonPressTimerHandle,
					Delegate,
					1.0f,
					false);

				GetWorld()->GetTimerManager().SetTimer(
					ButtonPressTimerHandle,
					this,
					&UCombatTabUserWidget::ButtonTimerReset,
					1.0f,
					false);
			}
		}
	}
}

//Item Button Functions

void UCombatTabUserWidget::Item1ButtonOnClicked()
{
	ItemFunction(2500, 4, 4, "Upgraded", UpgradeProperties[0].Damage, 
		UpgradeProperties[0].MPCost, UpgradeProperties[0].ItemCost, 0);

	if (GameInstanceRef->LockedButtons[4] == false)
	{
		Item1TextBlock->SetText(FText::FromString(
			"Damage: " + FString::FormatAsNumber(UpgradeProperties[0].Damage) +
			"\nMP: " + FString::FormatAsNumber(UpgradeProperties[0].MPCost) +
			"\nCost: " + FString::FormatAsNumber(UpgradeProperties[0].ItemCost)));
	}
}

void UCombatTabUserWidget::Item2ButtonOnClicked()
{
	ItemFunction(2500, 5, 5, "Upgraded", UpgradeProperties[1].Damage,
		UpgradeProperties[1].MPCost, UpgradeProperties[1].ItemCost, 1);

	if (GameInstanceRef->LockedButtons[5] == false)
	{
		Item2TextBlock->SetText(FText::FromString(
			"Damage: " + FString::FormatAsNumber(UpgradeProperties[1].Damage) +
			"\nMP: " + FString::FormatAsNumber(UpgradeProperties[1].MPCost) +
			"\nCost: " + FString::FormatAsNumber(UpgradeProperties[1].ItemCost)));
	}
}

void UCombatTabUserWidget::Item3ButtonOnClicked()
{
	ItemFunction(2500, 6, 6, "Upgraded", UpgradeProperties[2].Damage,
		UpgradeProperties[2].MPCost, UpgradeProperties[2].ItemCost, 2);


	if (GameInstanceRef->LockedButtons[6] == false)
	{
		Item3TextBlock->SetText(FText::FromString(
			"Damage: " + FString::FormatAsNumber(UpgradeProperties[2].Damage) +
			"\nMP: " + FString::FormatAsNumber(UpgradeProperties[2].MPCost) +
			"\nCost: " + FString::FormatAsNumber(UpgradeProperties[2].ItemCost)));
	}
}

void UCombatTabUserWidget::Item4ButtonOnClicked()
{
	ItemFunction(2500, 7, 7, "Upgraded", UpgradeProperties[3].Damage,
		UpgradeProperties[3].MPCost, UpgradeProperties[3].ItemCost, 3);

	if (GameInstanceRef->LockedButtons[7] == false)
	{
		Item4TextBlock->SetText(FText::FromString(
			"Damage: " + FString::FormatAsNumber(UpgradeProperties[3].Damage) +
			"\nMP: " + FString::FormatAsNumber(UpgradeProperties[3].MPCost) +
			"\nCost: " + FString::FormatAsNumber(UpgradeProperties[3].ItemCost)));
	}
}


FUpgradeProperties UCombatTabUserWidget::ItemUpgrade(int Damage, float MPCost, int ItemCost, int ItemIndex)
{
	FUpgradeProperties temp = UpgradeProperties[ItemIndex];

	if (PlayerRef->money >= ItemCost) {
		Damage += 1;
		MPCost -= 0.5;
		ItemCost = ItemCost + (ItemCost * 0.1);
		PlayerRef->money -= ItemCost;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::FormatAsNumber(ItemCost));
	}

	temp.Damage = Damage;
	temp.MPCost = MPCost;
	temp.ItemCost = ItemCost;

	return temp;
}

//Button Functions

void UCombatTabUserWidget::ButtonTimerReset()
{
	bCanClick = true;
	GetWorld()->GetTimerManager().ClearTimer(ButtonPressTimerHandle);
	
	if (GameInstanceRef->LockedButtons[0] == false)
	{
		Attack1TextBlock->SetText(FText::FromString("Normal \nAttack"));
	}

	if (GameInstanceRef->LockedButtons[1] == false)
	{
		Attack2TextBlock->SetText(FText::FromString("Fire \nAttack"));
	}

	if (GameInstanceRef->LockedButtons[2] == false)
	{
		Attack3TextBlock->SetText(FText::FromString("Grass \nAttack"));
	}

	if (GameInstanceRef->LockedButtons[3] == false)
	{
		Attack4TextBlock->SetText(FText::FromString("Water \nAttack"));
	}
}

void UCombatTabUserWidget::ChangeButtonText(UTextBlock* ButtonName, int ButtonNum)
{
	bCanClick = true;
	GetWorld()->GetTimerManager().ClearTimer(ButtonPressTimerHandle);

	switch (ButtonNum) 
	{
		case 1:
			ButtonName->SetText(FText::FromString("Normal Attack"));
			break;
		case 2:
			ButtonName->SetText(FText::FromString("Fire Attack"));
			break;
		case 3:
			ButtonName->SetText(FText::FromString("Grass Attack"));
			break;
		case 4:
			ButtonName->SetText(FText::FromString("Water Attack"));
			break;
	}
}

void UCombatTabUserWidget::IdleTimerReset()
{
	GetWorld()->GetTimerManager().ClearTimer(IdleFunctionTimerHandle);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Idle Timer Reset Called");
}


void UCombatTabUserWidget::IdleFunction()
{
	//it did work but didnt call Attack1Button more than once because of return 
	//but didnt know how to make it not infinite

	//If Button is on turn it off
	if (Idle == true)
	{
		Idle = false;
		IdleButtonTextBlock->SetText(FText::FromString("Idle: Off"));

		IdleTimerReset();
	}
	else if (Idle == false)
	{
		Idle = true;
		IdleButtonTextBlock->SetText(FText::FromString("Idle: On"));

		GetWorld()->GetTimerManager().SetTimer(
				IdleFunctionTimerHandle,
				this,
				&UCombatTabUserWidget::Attack1ButtonOnClicked,
				1.0f,
				true);
	}
}

void UCombatTabUserWidget::IdleButtonOnClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Idle Clicked");
	
	IdleFunction();
}

void UCombatTabUserWidget::CooldownText()
{
	if (GameInstanceRef->LockedButtons[0] == false)
	{
		Attack1TextBlock->SetText(FText::FromString("cooldown"));
	}

	if (GameInstanceRef->LockedButtons[1] == false)
	{
		Attack2TextBlock->SetText(FText::FromString("cooldown"));
	}

	if (GameInstanceRef->LockedButtons[2] == false)
	{
		Attack3TextBlock->SetText(FText::FromString("cooldown"));
	}

	if (GameInstanceRef->LockedButtons[3] == false)
	{
		Attack4TextBlock->SetText(FText::FromString("cooldown"));
	}
}

