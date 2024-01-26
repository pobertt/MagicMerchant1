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
	UpgradeProperties[0] = FUpgradeProperties(5, 15.f, 10, 1.0f);

	bCanClick.Init(true, 4);

	ButtonPressTimerHandle.SetNum(4);	

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

		//First Click has been consumed
		GameInstanceRef->FirstClickArray[FirstClickArrayIndex] = false;
		return;
	}

	//If button is unlocked and the first click (purchase) is consumed 
	//and if mana can afford it 
	if (GameInstanceRef->LockedButtons[LockedButtonsIndex] == false && GameInstanceRef->FirstClickArray[FirstClickArrayIndex] == false && PlayerRef->mp > MPCost)
	{	
		//Checking if HP is greater than 0
		if (BaseEnemyRef->CurrentHP >= 0 && BaseEnemyRef->IsValidLowLevel())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Player Attack Enemy");
			//If greater then deal dmg and print text
			PlayerRef->AttackEnemy(Dmg, MPCost, AttackType);

			TextLabel->SetText(FText::FromString(AttackUsed));
		}
		else
		{
			TextLabel->SetText(FText::FromString("Enemy Killed"));
		}
	}
}

void UCombatTabUserWidget::Attack1ButtonOnClicked()
{
	if (bCanClick[0] == true && PlayerRef->mp > UpgradeProperties[0].MPCost)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Enemy Is Alive: " + FString::FormatAsNumber(BaseEnemyRef->isAlive));
		//The button now can't be clicked until Button Timer Reset is called
		bCanClick[0] = false;

		//Calling the Attack Function
		AttackFunction(0, 0, 0, UpgradeProperties[0].Damage,"Normal Attack Used", UpgradeProperties[0].MPCost, "Normal");
		
		//If the button is unlocked 
		if (GameInstanceRef->LockedButtons[0] == false)
		{
			//Set the specific button text to on cooldown
			CooldownText(Attack1TextBlock, 0);

			FTimerDelegate Delegate;

			//Assigning the function to the timer and passing in parameters 
			Delegate.BindUFunction(this, "ChangeButtonText", Attack1TextBlock, 0);

			//Set this specific timer back to the original text
			GetWorld()->GetTimerManager().SetTimer(
				ButtonPressTimerHandle[0],
				Delegate,
				UpgradeProperties[0].CooldownTime,
				false);
		}
	}
}

void UCombatTabUserWidget::Attack2ButtonOnClicked()
{
	if (Idle == false)
	{
		if (bCanClick[1] == true && PlayerRef->mp > UpgradeProperties[1].MPCost)
		{
			bCanClick[1] = false;
			AttackFunction(25, 1, 1, UpgradeProperties[1].Damage, "Fire Attack Used", UpgradeProperties[1].MPCost, "Fire");

			if (GameInstanceRef->LockedButtons[1] == false)
			{
				CooldownText(Attack2TextBlock, 1);

				FTimerDelegate Delegate;
				Delegate.BindUFunction(this, "ChangeButtonText", Attack2TextBlock, 1);

				GetWorld()->GetTimerManager().SetTimer(
					ButtonPressTimerHandle[1],
					Delegate,
					UpgradeProperties[1].CooldownTime,
					false);
			}
		}
	}
}

void UCombatTabUserWidget::Attack3ButtonOnClicked()
{
	if (Idle == false)
	{
		if (bCanClick[2] == true && PlayerRef->mp > UpgradeProperties[2].MPCost)
		{
			bCanClick[2] = false;
			AttackFunction(25, 2, 2, UpgradeProperties[2].Damage, "Grass Attack Used", UpgradeProperties[2].MPCost, "Grass");

			if (GameInstanceRef->LockedButtons[2] == false)
			{
				CooldownText(Attack3TextBlock, 2);

				FTimerDelegate Delegate;
				Delegate.BindUFunction(this, "ChangeButtonText", Attack3TextBlock, 2);

				GetWorld()->GetTimerManager().SetTimer(
					ButtonPressTimerHandle[2],
					Delegate,
					UpgradeProperties[2].CooldownTime,
					false);
			}
		}
	}
}

void UCombatTabUserWidget::Attack4ButtonOnClicked()
{
	if (Idle == false)
	{
		if (bCanClick[3] == true && PlayerRef->mp > UpgradeProperties[3].MPCost)
		{
			bCanClick[3] = false;
			AttackFunction(25, 3, 3, UpgradeProperties[3].Damage, "Water Attack Used", UpgradeProperties[3].MPCost, "Water");

			if (GameInstanceRef->LockedButtons[3] == false)
			{
				CooldownText(Attack4TextBlock, 3);

				FTimerDelegate Delegate;
				Delegate.BindUFunction(this, "ChangeButtonText", Attack4TextBlock, 3);

				GetWorld()->GetTimerManager().SetTimer(
					ButtonPressTimerHandle[3],
					Delegate,
					UpgradeProperties[3].CooldownTime,
					false);
			}
		}
	}
}

void UCombatTabUserWidget::IdleButtonOnClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Idle Clicked");

	IdleFunction();
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

void UCombatTabUserWidget::ChangeButtonText(UTextBlock* ButtonName, int ButtonNum)
{
	bCanClick[ButtonNum] = true;
	GetWorld()->GetTimerManager().ClearTimer(ButtonPressTimerHandle[ButtonNum]);

	switch (ButtonNum)
	{
	case 0:
		ButtonName->SetText(FText::FromString("Normal \nAttack"));
		break;
	case 1:
		ButtonName->SetText(FText::FromString("Fire \nAttack"));
		break;
	case 2:
		ButtonName->SetText(FText::FromString("Grass \nAttack"));
		break;
	case 3:
		ButtonName->SetText(FText::FromString("Water \nAttack"));
		break;
	}
}

void UCombatTabUserWidget::CooldownText(UTextBlock* ButtonName, int ButtonNum)
{
	switch (ButtonNum)
	{
	case 0:
		ButtonName->SetText(FText::FromString("cooldown: \n" + FString::SanitizeFloat(UpgradeProperties[0].CooldownTime)));
		break;
	case 1:
		ButtonName->SetText(FText::FromString("cooldown: \n" + FString::SanitizeFloat(UpgradeProperties[1].CooldownTime)));
		break;
	case 2:
		ButtonName->SetText(FText::FromString("cooldown: \n" + FString::SanitizeFloat(UpgradeProperties[2].CooldownTime)));
		break;
	case 3:
		ButtonName->SetText(FText::FromString("cooldown: \n" + FString::SanitizeFloat(UpgradeProperties[3].CooldownTime)));
		break;
	}
}


//Item Button Functions

void UCombatTabUserWidget::ItemFunction(int Cost, int LockedButtonsIndex, int FirstClickArrayIndex, FString ItemUsed, int Damage, float MPCost, int ItemCost, float CooldownTime, int ItemIndex)
{
	if (PlayerRef->money < Cost && GameInstanceRef->LockedButtons[LockedButtonsIndex] == true)
	{
		TextLabel->SetText(FText::FromString("LOCKED"));
	}
	else if (GameInstanceRef->FirstClickArray[FirstClickArrayIndex] == true) 
	{
		GameInstanceRef->LockedButtons[LockedButtonsIndex] = false;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FormatAsNumber(ItemCost));

		TextLabel->SetText(FText::FromString("Purchased"));

		GameInstanceRef->FirstClickArray[FirstClickArrayIndex] = false;

		PlayerRef->money = PlayerRef->SubMoney(Cost);
		return;
	}
	if (GameInstanceRef->LockedButtons[LockedButtonsIndex] == false && GameInstanceRef->FirstClickArray[FirstClickArrayIndex] == false && PlayerRef->money >= ItemCost)
	{
		TextLabel->SetText(FText::FromString(ItemUsed));
		
		UpgradeProperties[ItemIndex] = ItemUpgrade(Damage, MPCost, ItemCost, CooldownTime, ItemIndex);

		PlayerRef->money = PlayerRef->SubMoney(ItemCost);
	}
}

void UCombatTabUserWidget::Item1ButtonOnClicked()
{
	ItemFunction(25, 4, 4, "Upgraded", UpgradeProperties[0].Damage, 
		UpgradeProperties[0].MPCost, UpgradeProperties[0].ItemCost, UpgradeProperties[0].CooldownTime, 0);

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
	ItemFunction(25, 5, 5, "Upgraded", UpgradeProperties[1].Damage,
		UpgradeProperties[1].MPCost, UpgradeProperties[1].ItemCost, UpgradeProperties[1].CooldownTime, 1);

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
	ItemFunction(25, 6, 6, "Upgraded", UpgradeProperties[2].Damage,
		UpgradeProperties[2].MPCost, UpgradeProperties[2].ItemCost, UpgradeProperties[2].CooldownTime, 2);


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
	ItemFunction(25, 7, 7, "Upgraded", UpgradeProperties[3].Damage,
		UpgradeProperties[3].MPCost, UpgradeProperties[3].ItemCost, UpgradeProperties[3].CooldownTime, 3);

	if (GameInstanceRef->LockedButtons[7] == false)
	{
		Item4TextBlock->SetText(FText::FromString(
			"Damage: " + FString::FormatAsNumber(UpgradeProperties[3].Damage) +
			"\nMP: " + FString::FormatAsNumber(UpgradeProperties[3].MPCost) +
			"\nCost: " + FString::FormatAsNumber(UpgradeProperties[3].ItemCost)));
	}
}


FUpgradeProperties UCombatTabUserWidget::ItemUpgrade(int Damage, float MPCost, int ItemCost, float CooldownTime, int ItemIndex)
{
	FUpgradeProperties temp = UpgradeProperties[ItemIndex];
	
	if (PlayerRef->money >= ItemCost)
	{
		if (ItemIndex == 0)
		{
			if (CooldownTime > 0.2f)
			{
				CooldownTime = CooldownTime - 0.1f;
			}
			if (MPCost > 0.0f)
			{
				MPCost = MPCost - 0.5;
			}

			Damage += 1;

			ItemCost = ItemCost + (ItemCost * 0.1);
		}
		else
		{
			if (CooldownTime > 1.0f)
			{
				CooldownTime = CooldownTime - 0.5f;
			}
			if (MPCost > 2.0f)
			{
				MPCost = MPCost - 1.0f;
			}

			Damage += 1;

			ItemCost = ItemCost + (ItemCost * 0.1);
		}

		temp.Damage = Damage;
		temp.MPCost = MPCost;
		temp.ItemCost = ItemCost;
		temp.CooldownTime = CooldownTime;

		return temp;
	}

	return temp;
}
