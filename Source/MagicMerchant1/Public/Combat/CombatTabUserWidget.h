// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicMerchant1\MagicMerchant1GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "BetterPlayerCharacter.h"
#include "Combat/BaseEnemy.h"
#include "CombatTabUserWidget.generated.h"


/**
 * 
 */
UCLASS()
class MAGICMERCHANT1_API UCombatTabUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CombatWidgetVariables, meta = (AllowPrivateAccess = "true"))
		bool Locked = true;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CombatWidgetVariables, meta = (AllowPrivateAccess = "true"))
		uint8 FirstClick = 1;


	//Combat Tab Widget Text Variables

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TextLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Attack1TextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Attack2TextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Attack3TextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Attack4TextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Item1TextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Item2TextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Item3TextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Item4TextBlock;

	//Enemy Variables

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* EnemyHPText;

	//Combat Tab Widget Button Variables

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Attack1Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Attack2Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Attack3Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Attack4Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Item1Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Item2Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Item3Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Item4Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* BackButton;

	virtual void NativeConstruct() override;

	//Attack Functions

	UFUNCTION()
		void AttackFunction(int Cost, int LockedButtonsIndex, int FirstClickArrayIndex, int Dmg, FString AttackUsed);

	UFUNCTION()
		void ItemFunction(int Cost, int LockedButtonsIndex, int FirstClickArrayIndex);

	UFUNCTION()
		void Attack1ButtonOnClicked();

	UFUNCTION()
		void Attack2ButtonOnClicked();

	UFUNCTION()
		void Attack3ButtonOnClicked();

	UFUNCTION()
		void Attack4ButtonOnClicked();

	//Item Functions

	UFUNCTION()
		void Item1ButtonOnClicked();

	UFUNCTION()
		void Item2ButtonOnClicked();

	UFUNCTION()
		void Item3ButtonOnClicked();

	UFUNCTION()
		void Item4ButtonOnClicked();

	//Button Functions

	UFUNCTION()
		void BackButtonOnClicked();

private:

	//Game References

	class AMagicMerchant1GameModeBase* GamemodeRef;

	class ABetterPlayerCharacter* PlayerRef;

	class ABaseEnemy* BaseEnemyRef;

	TArray<bool> LockedButtons;

	TArray<bool> FirstClickArray;
};
