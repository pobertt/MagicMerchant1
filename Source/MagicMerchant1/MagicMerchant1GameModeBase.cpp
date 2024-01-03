// Copyright Epic Games, Inc. All Rights Reserved.


#include "MagicMerchant1GameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

AMagicMerchant1GameModeBase::AMagicMerchant1GameModeBase()
{
	
}

void AMagicMerchant1GameModeBase::BeginPlay()
{
	//Creating CombatWidget and checking if it exists	
	if (IsValid(WidgetClass))
	{
		//Creating CombatWidget - Cast 
		CombatWidget = Cast<UCombatTabUserWidget>(CreateWidget(GetWorld(), WidgetClass));

		//Checking whether or not CombatWidget was created successfully 
		if(CombatWidget != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "UI is Active");
			
			return;
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "This UI is not Active");
		}

		
	}
}

void AMagicMerchant1GameModeBase::Tick(float DeltaTime)
{

}

void AMagicMerchant1GameModeBase::AddCombatWidget()
{
	//Creating combat widget
	CombatWidget = Cast<UCombatTabUserWidget>(CreateWidget(GetWorld(), WidgetClass));
	CombatWidget->AddToViewport();

	
	

	//When the combat widget is redadded it will create a new enemy
	//PlayerRef->MakeEnemy();
}

void AMagicMerchant1GameModeBase::RemoveCombatWidget()
{
	//Destroy Combat Widget and BaseEnemy Actor
	CombatWidget->RemoveFromParent();
	CombatWidget->Destruct();

	if (BaseEnemyRef->IsValidLowLevel())
	{
		//Blueprint is doing this:
		//BaseEnemyRef->Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Enemy Valid");
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Enemy not Valid");
	}
		
	//UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
}

void AMagicMerchant1GameModeBase::AddMainUIWidget()
{
	//UUserWidget* UI = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), *MainUIClass);
	//UI->AddToViewport();
}

void AMagicMerchant1GameModeBase::RemoveMainUIWidget()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
}

void AMagicMerchant1GameModeBase::SetEnemyRef(AActor* enemy)
{
	BaseEnemyRef = Cast<ABaseEnemy>(enemy);
}


