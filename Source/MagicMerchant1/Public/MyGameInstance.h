// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicMerchant1\MagicMerchant1GameModeBase.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MAGICMERCHANT1_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	//Constructor 
	UMyGameInstance();

	//References 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AMagicMerchant1GameModeBase* GamemodeRef;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// class ABetterPlayerCharacter* PlayerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABaseEnemy* BaseEnemyRef;

	//Combat Widget Reference
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UCombatTabUserWidget* CombatWidget;

	TArray<bool> LockedButtons;

	TArray<bool> FirstClickArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FString> ButtonText;

	UPROPERTY()
		int32 InitialCost;

	UFUNCTION()
		void SetEnemyUIType(uint8 SpawnNum);

private:

	int32 NumButtons;

	UPROPERTY(EditAnywhere, Category = "Class Types")
		TSubclassOf<UUserWidget> FireEnemyUIClass;

};

/*
Native construct for Widget
{
	Get reference to Game logic;
	AttackButtons.GetWhatIsUnlocked(GameLogicRef.Unlocks());
	Enemy Alive ?
}

Game Logic Class "GameInstance Class"

properties:
Player Reference;
Enemy Reference :
Player Unlocks;
Score ? ;

initializer function()
*/

//make enemy function?
//or maybe make enemy function in enemy and call it here on creation

//Locked button states and general unlocking states

//maybe item and attack function in here so it is called when idle is on