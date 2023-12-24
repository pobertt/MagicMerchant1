// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemy.generated.h"

UCLASS()
class MAGICMERCHANT1_API ABaseEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEnemy();

	//Enemy Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemyStats, meta = (AllowPrivateAccess = "true"))
		float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemyStats, meta = (AllowPrivateAccess = "true"))
		float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemyStats, meta = (AllowPrivateAccess = "true"))
		float HPRegen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemyStats, meta = (AllowPrivateAccess = "true"))
		int32 BaseAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemyStats, meta = (AllowPrivateAccess = "true"))
		float AttackMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemyStats, meta = (AllowPrivateAccess = "true"))
		int32 Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemyStats, meta = (AllowPrivateAccess = "true"))
		float DefenseMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemyStats, meta = (AllowPrivateAccess = "true"))
		float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemyStats, meta = (AllowPrivateAccess = "true"))
		bool isAlive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemyStats, meta = (AllowPrivateAccess = "true"))
		FString EnemyType;

	UFUNCTION(BlueprintCallable, Category = BaseEnemy)
	void ResetHealth();
	
	UFUNCTION(BlueprintCallable, Category = BaseEnemy)
		void InitBaseEnemy();

	UFUNCTION(BlueprintCallable, Category = TypeEnemy)
	void SetType(FString Type);

	UFUNCTION(BlueprintCallable, Category =	TypeEnemy)
	virtual FString GetType();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};

UCLASS()
class MAGICMERCHANT1_API AFireTypeEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
	AFireTypeEnemy();
};

UCLASS()
class MAGICMERCHANT1_API AGrassTypeEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
	AGrassTypeEnemy();
};

UCLASS()
class MAGICMERCHANT1_API AWaterTypeEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
	AWaterTypeEnemy();
};