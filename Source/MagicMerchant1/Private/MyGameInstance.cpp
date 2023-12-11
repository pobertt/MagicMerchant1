// Fill out your copyright notice in the Description page of Project Settings.
#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance() : NumButtons(9)
{
	for (int i = 0; i < NumButtons; i++)
	{
		LockedButtons.Push(true);
		FirstClickArray.Push(true);
		ButtonText.Push("LOCKED \n Cost: ");
		UE_LOG(LogTemp, Warning, TEXT("Button %i says: %s"), i, *ButtonText[i]);
	}
}
