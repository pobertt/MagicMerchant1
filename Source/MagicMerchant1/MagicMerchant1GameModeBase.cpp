// Copyright Epic Games, Inc. All Rights Reserved.


#include "MagicMerchant1GameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"



void AMagicMerchant1GameModeBase::BeginPlay()
{

	//Creating CombatWidget and checking if it exists
	if (IsValid(WidgetClass))
	{
		//Creating CombatWidget - Cast 
		CombatWidget = Cast<UCombatTabUserWidget>(CreateWidget(GetWorld(), WidgetClass));
		
		//Grabbing reference to main ui blueprint
		static ConstructorHelpers::FClassFinder<UUserWidget>MainUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UserInterface/WBP_UI.WBP_UI'"));
		
		//Checking whether or not CombatWidget was created successfully 
		if(CombatWidget != nullptr && !MainUI.Succeeded())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "UI is Active");
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "This UI is NOT Active");
			//Grabbing reference to MainUIClass
			MainUIClass = MainUI.Class;
		}

		// UE_LOG(LogTemp, Warning, TEXT("Main UI Class: %s"), *MainUIClass->GetName());

	}
}



void AMagicMerchant1GameModeBase::AddCombatWidget()
{
	CombatWidget->AddToViewport();

}

void AMagicMerchant1GameModeBase::RemoveCombatWidget()
{
	CombatWidget->RemoveFromParent();
}

void AMagicMerchant1GameModeBase::AddMainUIWidget()
{
	// UUserWidget* UI = CreateWidget<UUserWidget>(this, *MainUIClass);
	// UI->AddToViewport();
}

void AMagicMerchant1GameModeBase::RemoveMainUIWidget()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
}

