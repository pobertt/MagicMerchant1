// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Combat/BaseEnemy.h"
#include "Math/UnrealMathUtility.h"
// #include "MagicMerchant1/MagicMerchant1GameModeBase.h"
#include "BetterPlayerCharacter.generated.h"

UCLASS()
class MAGICMERCHANT1_API ABetterPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties

	ABetterPlayerCharacter();

	//Player Stats

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerStats, meta = (AllowPrivateAccess = "true"))
		int32 hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerStats, meta = (AllowPrivateAccess = "true"))
		int32 mp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerStats, meta = (AllowPrivateAccess = "true"))
		float money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerStats, meta = (AllowPrivateAccess = "true"))
		float currency2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerStats, meta = (AllowPrivateAccess = "true"))
		int32 lvl;

	//CombatStats

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerCombatStats, meta = (AllowPrivateAccess = "true"))
		int32 basicAttackDMG;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerCombatStats, meta = (AllowPrivateAccess = "true"))
		float MyFloat;

	//Inventory

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
		class UDataTable* Inventory;

	//Declaring functions to add to player stats

	UFUNCTION(BlueprintCallable, Category = playerStats)
		int32 AddHp();

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

	//Combat Functions

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

	//Base Enemy Reference
	UPROPERTY(BlueprintReadWrite)
	class ABaseEnemy* BaseEnemyRef;

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
