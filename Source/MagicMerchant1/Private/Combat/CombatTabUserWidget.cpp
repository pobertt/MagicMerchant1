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
	if (Attack1Button && Attack2Button && Attack3Button && Attack4Button && Item1Button && Item2Button && Item3Button && Item4Button && BackButton && IdleButton )
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
		IdleButton->OnClicked.AddDynamic(this, &UCombatTabUserWidget::IdleButtonOnClicked);
	}

	GamemodeRef = Cast<AMagicMerchant1GameModeBase>(GetWorld()->GetAuthGameMode());
	PlayerRef = Cast<ABetterPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	PlayerRef->MakeEnemy();
	BaseEnemyRef = PlayerRef->BaseEnemyRef;
}

//Attack Button Functions 

void UCombatTabUserWidget::AttackFunction(int Cost, int LockedButtonsIndex, int FirstClickArrayIndex, int Dmg, FString AttackUsed)
{
	//Checks the cost of the button and whether the button is in the locked state
	if (PlayerRef->money < Cost && LockedButtons[LockedButtonsIndex] == true)
	{
		//If true then say button is LOCKED
		TextLabel->SetText(FText::FromString("LOCKED"));
	}

	//Move onto this statemnent if player has enough money for the button 
	//(will always purchase if player has enough money anyways)
	else if (FirstClickArray[FirstClickArrayIndex] == true) {

		//Unlock's the button
		LockedButtons[LockedButtonsIndex] = false;

		//Minusing the cost of the button from player money
		PlayerRef->money = PlayerRef->SubMoney(Cost);

		//Output text saying it is purchased
		TextLabel->SetText(FText::FromString("Purchased"));

		//First Click has been consumed
		FirstClickArray[FirstClickArrayIndex] = false;
		return;
	}

	//If button is unlocked and the first click (purchase) is consumed 
	if (LockedButtons[LockedButtonsIndex] == false && FirstClickArray[FirstClickArrayIndex] == false)
	{
		//Checking if HP is greater than 0
		if (BaseEnemyRef->CurrentHP > 0)
		{
			//If greater then deal dmg and print text
			PlayerRef->AttackEnemy(Dmg);
			TextLabel->SetText(FText::FromString(AttackUsed));
			EnemyHPText->SetText(FText::AsNumber(BaseEnemyRef->CurrentHP));
		}
		else if (BaseEnemyRef->CurrentHP == 0)
		{
			//Kill the enemy if health is 0
			PlayerRef->EnemyKilled();
			TextLabel->SetText(FText::FromString("Enemy Killed"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Enemy Killed");
		}
	}
}

void UCombatTabUserWidget::ItemFunction(int Cost, int LockedButtonsIndex, int FirstClickArrayIndex)
{
	if (PlayerRef->money < Cost && LockedButtons[LockedButtonsIndex] == true)
	{
		TextLabel->SetText(FText::FromString("LOCKED"));
	}
	else if (FirstClickArray[FirstClickArrayIndex] == true) {
		LockedButtons[LockedButtonsIndex] = false;

		PlayerRef->money = PlayerRef->SubMoney(Cost);
		TextLabel->SetText(FText::FromString("Purchased"));

		FirstClickArray[FirstClickArrayIndex] = false;
		return;
	}

	if (LockedButtons[LockedButtonsIndex] == false && FirstClickArray[FirstClickArrayIndex] == false)
	{
		TextLabel->SetText(FText::FromString("Item consumed"));
		//item consumed function goes here
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
		AttackFunction(0, 0, 0, 5, "Attack 1 Used");
		
		//If the button is unlocked 
		if (LockedButtons[0] == false)
		{
			//Set the all button text to on cooldown
			CooldownText();

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
			AttackFunction(1000, 1, 1, 10, "Attack 2 Used");

			if (LockedButtons[1] == false)
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
			AttackFunction(2500, 2, 2, 25, "Attack 3 Used");

			if (LockedButtons[2] == false)
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
			AttackFunction(5000, 3, 3, 50, "Attack 4 Used");

			if (LockedButtons[3] == false)
			{
				CooldownText();

				FTimerDelegate Delegate;
				Delegate.BindUFunction(this, "ChangeButtonText", Attack4TextBlock, 4);

				GetWorld()->GetTimerManager().SetTimer(
					ButtonPressTimerHandle,
					Delegate,
					5.0f,
					false);


				GetWorld()->GetTimerManager().SetTimer(
					ButtonPressTimerHandle,
					this,
					&UCombatTabUserWidget::ButtonTimerReset,
					5.0f,
					false);
			}
		}
	}
}

//Item Button Functions

void UCombatTabUserWidget::Item1ButtonOnClicked()
{
	ItemFunction(0, 4, 4);
	
	if (LockedButtons[4] == false)
	{
		Item1TextBlock->SetText(FText::FromString("Item 1"));
	}
}

void UCombatTabUserWidget::Item2ButtonOnClicked()
{
	ItemFunction(2000, 5, 5);
	
	if (LockedButtons[5] == false)
	{
		Item2TextBlock->SetText(FText::FromString("Item 2"));
	}
}

void UCombatTabUserWidget::Item3ButtonOnClicked()
{
	ItemFunction(5000, 5, 5);

	if (LockedButtons[5] == false)
	{
		Item3TextBlock->SetText(FText::FromString("Item 3"));
	}
}

void UCombatTabUserWidget::Item4ButtonOnClicked()
{
	ItemFunction(10000, 6, 6);

	if (LockedButtons[6] == false)
	{
		Item4TextBlock->SetText(FText::FromString("Item 4"));
	}
}

//Button Functions

void UCombatTabUserWidget::ButtonTimerReset()
{
	bCanClick = true;
	GetWorld()->GetTimerManager().ClearTimer(ButtonPressTimerHandle);
	
	if (LockedButtons[0] == false)
	{
		Attack1TextBlock->SetText(FText::FromString("Attack 1"));
	}

	if (LockedButtons[1] == false)
	{
		Attack2TextBlock->SetText(FText::FromString("Attack 2"));
	}

	if (LockedButtons[2] == false)
	{
		Attack3TextBlock->SetText(FText::FromString("Attack 3"));
	}

	if (LockedButtons[3] == false)
	{
		Attack4TextBlock->SetText(FText::FromString("Attack 4"));
	}
}

void UCombatTabUserWidget::ChangeButtonText(UTextBlock* ButtonName, int ButtonNum)
{
	bCanClick = true;
	GetWorld()->GetTimerManager().ClearTimer(ButtonPressTimerHandle);

	switch (ButtonNum) 
	{
		case 1:
			ButtonName->SetText(FText::FromString("Attack 1"));
			break;
		case 2:
			ButtonName->SetText(FText::FromString("Attack 2"));
			break;
		case 3:
			ButtonName->SetText(FText::FromString("Attack 3"));
			break;
		case 4:
			ButtonName->SetText(FText::FromString("Attack 4"));
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

void UCombatTabUserWidget::BackButtonOnClicked()
{
	TextLabel->SetText(FText::FromString("BackPressed"));
	//BackButton pressed
	GamemodeRef->RemoveCombatWidget();
	//Display main ui again
	GamemodeRef->AddMainUIWidget();
}

void UCombatTabUserWidget::IdleButtonOnClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Idle Clicked");
	
	IdleFunction();
}

void UCombatTabUserWidget::CooldownText()
{
	if (LockedButtons[0] == false)
	{
		Attack1TextBlock->SetText(FText::FromString("cooldown"));
	}

	if (LockedButtons[1] == false)
	{
		Attack2TextBlock->SetText(FText::FromString("cooldown"));
	}

	if (LockedButtons[2] == false)
	{
		Attack3TextBlock->SetText(FText::FromString("cooldown"));
	}

	if (LockedButtons[3] == false)
	{
		Attack4TextBlock->SetText(FText::FromString("cooldown"));
	}
}

