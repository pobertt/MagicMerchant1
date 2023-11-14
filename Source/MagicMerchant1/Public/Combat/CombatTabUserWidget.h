// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

	virtual void NativeConstruct() override;

	UFUNCTION()
		void Attack1ButtonOnClicked();


};
