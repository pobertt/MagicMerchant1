// Fill out your copyright notice in the Description page of Project Settings.
#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance() : NumButtons(9), InitialCost(0)
{

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
			InitialCost = 0;
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
