// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/Combat/CombatTabUserWidget.h"
#include "Combat/BaseEnemy.h"
#include "BetterPlayerCharacter.h"
#include "MagicMerchant1GameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class MAGICMERCHANT1_API AMagicMerchant1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddCombatWidget();

	UFUNCTION(BlueprintCallable)
	void RemoveCombatWidget();

	UFUNCTION(BlueprintCallable)
	void AddMainUIWidget();

	UFUNCTION(BlueprintCallable)
	void RemoveMainUIWidget();

protected:
	UPROPERTY(EditAnywhere, Category = "Class Types")
	//specifying a base class in c++ and assigning a specific class inside of blueprints 
	TSubclassOf<UUserWidget> WidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "Class Types")
	//specifying a base class in c++ and assigning a specific class inside of blueprints 
	TSubclassOf<UUserWidget> MainUIClass;

	//Combat Widget Reference
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UCombatTabUserWidget* CombatWidget;

	//Base Enemy Reference
	class ABaseEnemy* BaseEnemyRef;

	//Player Reference
	class ABetterPlayerCharacter* PlayerRef;

	virtual void BeginPlay() override;
};
