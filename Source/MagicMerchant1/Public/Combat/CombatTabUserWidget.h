// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
USTRUCT()
struct FUpgradeProperties
{
	GENERATED_USTRUCT_BODY()
		
public:
	UPROPERTY()
		int Damage;

		UPROPERTY()
		float MPCost;

		UPROPERTY()
		int ItemCost;

		FUpgradeProperties(int InDamage = 15, float InMPCost = 25.f, int InItemCost = 25)
		{
			Damage = InDamage;
			MPCost = InMPCost;
			ItemCost = InItemCost;
		};
};

UCLASS()
class MAGICMERCHANT1_API UCombatTabUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
		TArray<FUpgradeProperties> UpgradeProperties;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CombatWidgetVariables, meta = (AllowPrivateAccess = "true"))
		bool Idle = false;

	//Time variables

	TArray<bool> bCanClick;

	//Handles the delay between clicks
	TArray<FTimerHandle> ButtonPressTimerHandle;
	
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
		class UButton* IdleButton;

	UPROPERTY()
		FUpgradeProperties UpgradeProperties1;

	UPROPERTY()
		FUpgradeProperties UpgradeProperties2;

	UPROPERTY()
		FUpgradeProperties UpgradeProperties3;

	UPROPERTY()
		FUpgradeProperties UpgradeProperties4;


	virtual void NativeConstruct() override;

	//Attack Functions

	UFUNCTION(BlueprintCallable)
		void AttackFunction(int Cost, int LockedButtonsIndex, int FirstClickArrayIndex, int Dmg, FString AttackUsed, float MPCost, FString AttackType);
	
	UFUNCTION()
		void ItemFunction(int Cost, int LockedButtonsIndex, int FirstClickArrayIndex, FString ItemUsed, int Damage, float MPCost, int ItemCost, int ItemIndex);

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

	UFUNCTION()
		FUpgradeProperties ItemUpgrade(int Damage, float MPCost, int ItemCost, int ItemIndex);

	//Button Functions

	UFUNCTION()
		void IdleFunction();

	UFUNCTION()
		void IdleButtonOnClicked();

	UFUNCTION()
		void CooldownText(class UTextBlock* ButtonName, int ButtonNum);


	//Timer Functions

	UFUNCTION()
		void ChangeButtonText(class UTextBlock* ButtonName, int ButtonNum);

	UFUNCTION()
		void IdleTimerReset();

private:

	//Game References

	class AMagicMerchant1GameModeBase* GamemodeRef;

	class ABetterPlayerCharacter* PlayerRef;

	class ABaseEnemy* BaseEnemyRef;

	class UMyGameInstance* GameInstanceRef;


	//TArray<bool> LockedButtons;

	//TArray<bool> FirstClickArray;
};
