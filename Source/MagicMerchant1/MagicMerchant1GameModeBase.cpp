// Copyright Epic Games, Inc. All Rights Reserved.


#include "MagicMerchant1GameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"


void AMagicMerchant1GameModeBase::BeginPlay()
{

	//Creating CombatWidget and checking if it exists
	if (IsValid(WidgetClass))
	{
		//Creating CombatWidget - Cast 
		CombatWidget = Cast<UCombatTabUserWidget>(CreateWidget(GetWorld(), WidgetClass));

		//static ConstructorHelpers::FClassFinder<UUserWidget> MainUI(TEXT("/Game/UserInterface/WBP_UI.WBP_UI"));
		
		//Checking whether or not CombatWidget was created successfully 
		if(CombatWidget != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "This UI is Active");
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "This UI is NOT Active");
		}

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

