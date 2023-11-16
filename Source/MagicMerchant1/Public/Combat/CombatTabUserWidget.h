// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicMerchant1\MagicMerchant1GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "BetterPlayerCharacter.h"
#include "CombatTabUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MAGICMERCHANT1_API UCombatTabUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TextLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Attack1Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Item1Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* BackButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void Attack1ButtonOnClicked();

	UFUNCTION()
		void Item1ButtonOnClicked();

	UFUNCTION()
		void BackButtonOnClicked();

private:
	class AMagicMerchant1GameModeBase* GamemodeRef;

	class ABetterPlayerCharacter* PlayerRef;
};
