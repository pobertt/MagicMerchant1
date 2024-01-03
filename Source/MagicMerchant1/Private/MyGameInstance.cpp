// Fill out your copyright notice in the Description page of Project Settings.
#include "MyGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UMyGameInstance::UMyGameInstance() : NumButtons(9), InitialCost(0)
{

	//GamemodeRef = Cast<AMagicMerchant1GameModeBase>(GetWorld()->GetAuthGameMode());

	/*
	if (GamemodeRef->CombatWidget->Idle == true)
	{
		GamemodeRef->CombatWidget->IdleButtonTextBlock->SetText(FText::FromString("Idle: Off"));
	}
	else if (GamemodeRef->CombatWidget->Idle == false)
	{
		GamemodeRef->CombatWidget->IdleButtonTextBlock->SetText(FText::FromString("Idle: On"));
	}
	*/

	//Creating Enemy Widgets
	static ConstructorHelpers::FClassFinder<UUserWidget> FireEnemy(TEXT("/Game/UserInterface/WBP_FireEnemy"));

	if (FireEnemy.Succeeded())
	{
		FireEnemyUIClass = FireEnemy.Class;
		UE_LOG(LogTemp, Warning, TEXT("UI CLASS FOUND"));
	}

	for (int i = 0; i < NumButtons; i++)
	{
		LockedButtons.Push(true);
		FirstClickArray.Push(true);
		ButtonText.Push("LOCKED \n Cost:" + FString::FormatAsNumber(InitialCost));
		UE_LOG(LogTemp, Warning, TEXT("Button %i says: %s"), i, *ButtonText[i]);

		if (i == 0)
		{
			InitialCost = 1000;
		}
		else if (i == 1) 
		{
			InitialCost = 2500;
		}
		else if (i == 2)
		{
			InitialCost = 5000;
		}
		else if (i == 3)
		{
			InitialCost = 1000;
		}
		else if (i == 4)
		{
			InitialCost = 2500;
		}
		else if (i == 5)
		{
			InitialCost = 5000;
		}
		else if (i == 6)
		{
			InitialCost = 10000;
		}
	}
}

void UMyGameInstance::SetEnemyUIType(uint8 SpawnNum)
{
	switch (SpawnNum)
	{
	case 1:
	{
		UUserWidget* FireEnemyUI = CreateWidget<UUserWidget>(GetWorld(), *FireEnemyUIClass);
		FireEnemyUI->AddToViewport();
		return;
	}
	case 2:
	{
		return;
	}
	case 3:
	{
		return;
	}
	}
}
