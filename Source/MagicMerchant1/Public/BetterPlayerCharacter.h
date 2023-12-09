// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Combat/BaseEnemy.h"
#include "Math/UnrealMathUtility.h"
//#include "MagicMerchant1/MagicMerchant1GameModeBase.h"
#include "Combat\CombatTabUserWidget.h"
#include "TimerManager.h"
#include "Engine.h"
#include "BetterPlayerCharacter.generated.h"

UCLASS()
class MAGICMERCHANT1_API ABetterPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties

	ABetterPlayerCharacter();

	//Base Enemy Reference
	UPROPERTY()
	class ABaseEnemy* BaseEnemyRef;

	//Combat Widget Reference
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		class UCombatTabUserWidget* CombatWidget;

	//Health Stats

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HealthStats, meta = (AllowPrivateAccess = "true"))
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HealthStats, meta = (AllowPrivateAccess = "true"))
		float HealthRegen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HealthStats, meta = (AllowPrivateAccess = "true"))
		float HealthRate;

	FTimerHandle HealthRateTimerHandle;

	//Player Stats

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerStats, meta = (AllowPrivateAccess = "true"))
		int32 mp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerStats, meta = (AllowPrivateAccess = "true"))
		float money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerStats, meta = (AllowPrivateAccess = "true"))
		float currency2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerStats, meta = (AllowPrivateAccess = "true"))
		int32 lvl;

	//Combat Stats

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerCombatStats, meta = (AllowPrivateAccess = "true"))
		int32 basicAttackDMG;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerCombatStats, meta = (AllowPrivateAccess = "true"))
		float MyFloat;

	//Enemy Variables

	FTimerHandle EnemyRespawnTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BaseEnemy, meta = (AllowPrivateAccess = "true"))
		bool bEnemyRespawn = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BaseEnemy, meta = (AllowPrivateAccess = "true"))
		float RespawnDelayTimer;

	//Inventory

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
		class UDataTable* Inventory;

	//Declaring functions to add to player stats

	UFUNCTION(BlueprintCallable, Category = HealthStats)
		void HealthRegenBar();

	UFUNCTION(BlueprintCallable, Category = playerStats)
		float AddHp(float AddHealth);

	UFUNCTION(BlueprintCallable, Category = playerStats)
		int32 AddMp();

	UFUNCTION(BlueprintCallable, Category = playerStats)
		float AddMoney(float Amount);

	UFUNCTION(BlueprintCallable, Category = playerStats)
		float AddCurrency2();

	UFUNCTION(BlueprintCallable, Category = playerStats)
		int32 AddLvl();

	//Declaring functions to subtract from player stats

	UFUNCTION(BlueprintCallable, Category = playerStats)
		int32 SubHp();

	UFUNCTION(BlueprintCallable, Category = playerStats)
		int32 SubMp();

	UFUNCTION(BlueprintCallable, Category = playerStats)
		float SubMoney(int Cost);

	UFUNCTION(BlueprintCallable, Category = playerStats)
		float SubCurrency2();

	UFUNCTION(BlueprintCallable, Category = playerStats)
		int32 SubLvl();

	UFUNCTION(BlueprintImplementableEvent, Category = playerStats)
		void SayHey();
	void SayHey_Implementation() { };

	//Enenmy Functions

	UFUNCTION(BlueprintCallable, Category = BaseEnemy)
		void MakeEnemy();

	UFUNCTION(BlueprintCallable, Category = playerCombat)
		void AttackEnemy(int Dmg);

	UFUNCTION(BlueprintCallable, Category = BaseEnemy)
		void EnemyKilled();

	UFUNCTION(BlueprintCallable, Category = BaseEnemy)
		void EnemyRespawn();

	UFUNCTION(BlueprintCallable, Category = BaseEnemy)
		void InitBaseEnemy();

	UFUNCTION(BlueprintCallable, Category = BaseEnemy)
		void EnemySpawnDelay();

	//Timer Functions

	UFUNCTION()
		void HealthTimerReset();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

};
