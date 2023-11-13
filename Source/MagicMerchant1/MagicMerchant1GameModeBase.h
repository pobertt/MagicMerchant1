// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MagicMerchant1GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MAGICMERCHANT1_API AMagicMerchant1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
/*

protected:
	UPROPERTY(EditAnywhere, Category = "Class Types")
	//specifying a base class in c++ and assigning a specific class inside of blueprints 
	TSubclassOf<UUserWidget> WidgetClass;

	//Displaying widget to viewport instead of doing it in blueprints
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UCombatTabUserWidget* ButtonWidget;

	virtual void BeginPlay() override;
	*/
};
