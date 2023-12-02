// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicMerchant1\MagicMerchant1GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "BetterPlayerCharacter.h"
#include "Combat/BaseEnemy.h"
#include "MyGameInstance.h"
#include "TimerManager.h"
#include "Engine.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CombatWidgetVariables, meta = (AllowPrivateAccess = "true"))
		bool Idle = false;

	//Time variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CombatWidgetVariables, meta = (AllowPrivateAccess = "true"))
		bool bCanClick = true;

	//Handles the delay between clicks
	FTimerHandle ButtonPressTimerHandle;

	FTimerHandle IdleFunctionTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CombatWidgetVariables, meta = (AllowPrivateAccess = "true"))
		float DelayTimer;

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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* IdleButtonTextBlock;

	//Enemy Variables

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* EnemyHPText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UImage* BaseEnemyImg;

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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* IdleButton;

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
		void IdleFunction();

	UFUNCTION()
		void BackButtonOnClicked();

	UFUNCTION()
		void IdleButtonOnClicked();

	UFUNCTION()
		void CooldownText();

	//Timer Functions

	UFUNCTION()
		void ButtonTimerReset();

	UFUNCTION()
		void ChangeButtonText(class UTextBlock* ButtonName, int ButtonNum);

	UFUNCTION()
		void IdleTimerReset();


private:

	//Game References

	class AMagicMerchant1GameModeBase* GamemodeRef;

	class ABetterPlayerCharacter* PlayerRef;

	class ABaseEnemy* BaseEnemyRef;

	TArray<bool> LockedButtons;

	TArray<bool> FirstClickArray;
};
