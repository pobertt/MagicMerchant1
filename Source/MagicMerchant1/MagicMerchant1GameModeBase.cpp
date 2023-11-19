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
		//static ConstructorHelpers::FClassFinder<UUserWidget> MainUI(TEXT("/Game/UserInterface/WBP_UI"));
		//&& MainUI.Succeeded()
		//Checking whether or not CombatWidget was created successfully 
		if(CombatWidget != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "UI is Active");
			return;
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "This UI is not Active");
			//Grabbing reference to MainUIClass
			// MainUIClass = MainUI.Class;
		}
	}
	//Getting player Ref
	PlayerRef = Cast<ABetterPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerRef->IsValidLowLevel())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Player Exists");
	}
	else {

		 GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Player Does not  Exists");
	}
}



void AMagicMerchant1GameModeBase::AddCombatWidget()
{
	//Creating combat widget
	CombatWidget = Cast<UCombatTabUserWidget>(CreateWidget(GetWorld(), WidgetClass));
	CombatWidget->AddToViewport();

	PlayerRef->MakeEnemy();
}

void AMagicMerchant1GameModeBase::RemoveCombatWidget()
{
	//Destroy Combat Widget and BaseEnemy Actor
	CombatWidget->RemoveFromParent();
	CombatWidget->Destruct();
	//BaseEnemyRef->Destroy();
	//UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
}

void AMagicMerchant1GameModeBase::AddMainUIWidget()
{
	// UUserWidget* UI = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), *MainUIClass);
	// UI->AddToViewport();
}

void AMagicMerchant1GameModeBase::RemoveMainUIWidget()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
}

