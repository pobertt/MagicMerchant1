// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/Combat/CombatTabUserWidget.h"
#include "Combat/BaseEnemy.h"
#include "MagicMerchant1GameModeBase.generated.h"

//enum to store the current state of gameplay
UENUM()
enum class EGamePlayState 
{
	EPlaying,
	EGameOver,
	EUnknown
};

UCLASS()
class MAGICMERCHANT1_API AMagicMerchant1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	//Base Enemy Reference
	UPROPERTY()
	class ABaseEnemy* BaseEnemyRef;

	//Combat Widget Reference
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UCombatTabUserWidget* CombatWidget;

	AMagicMerchant1GameModeBase();

	UFUNCTION(BlueprintCallable)
	void AddCombatWidget();

	UFUNCTION(BlueprintCallable)
	void RemoveCombatWidget();

	UFUNCTION(BlueprintCallable)
	void AddMainUIWidget();

	UFUNCTION(BlueprintCallable)
	void RemoveMainUIWidget();

	UFUNCTION()
	void SetEnemyRef(AActor* enemy);


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:
	//Keeps track of the current playing state
	EGamePlayState CurrentState;

	UPROPERTY(EditAnywhere, Category = "Class Types")
	//specifying a base class in c++ and assigning a specific class inside of blueprints 
	TSubclassOf<UUserWidget> WidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "Class Types")
	//specifying a base class in c++ and assigning a specific class inside of blueprints 
	TSubclassOf<UUserWidget> MainUIClass;



};
