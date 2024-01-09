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

	static ConstructorHelpers::FClassFinder<UUserWidget> GrassEnemy(TEXT("/Game/UserInterface/WBP_GrassEnemy"));

	static ConstructorHelpers::FClassFinder<UUserWidget> WaterEnemy(TEXT("/Game/UserInterface/WBP_WaterEnemy"));

	if (FireEnemy.Succeeded() && GrassEnemy.Succeeded() && WaterEnemy.Succeeded())
	{
		FireEnemyUIClass = FireEnemy.Class;

		GrassEnemyUIClass = GrassEnemy.Class;

		WaterEnemyUIClass = WaterEnemy.Class;
	}

	for (int i = 0; i < NumButtons; i++)
	{
		LockedButtons.Push(true);
		FirstClickArray.Push(true);
		ButtonText.Push("LOCKED \n Cost:" + FString::FormatAsNumber(InitialCost));
		UE_LOG(LogTemp, Warning, TEXT("Button %i says: %s"), i, *ButtonText[i]);

		if (i == 0)
		{
			InitialCost = 250;
		}
		else if (i == 1) 
		{
			InitialCost = 250;
		}
		else if (i == 2)
		{
			InitialCost = 250;
		}
		else if (i == 3)
		{
			InitialCost = 50;
		}
		else if (i == 4)
		{
			InitialCost = 250;
		}
		else if (i == 5)
		{
			InitialCost = 250;
		}
		else if (i == 6)
		{
			InitialCost = 250;
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
		UUserWidget* GrassEnemyUI = CreateWidget<UUserWidget>(GetWorld(), *GrassEnemyUIClass);
		GrassEnemyUI->AddToViewport();
		return;
	}
	case 3:
	{
		UUserWidget* WaterEnemyUI = CreateWidget<UUserWidget>(GetWorld(), *WaterEnemyUIClass);
		WaterEnemyUI->AddToViewport();
		return;
	}
	}
}
