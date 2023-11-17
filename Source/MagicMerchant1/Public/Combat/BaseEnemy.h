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
		int32 MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemyStats, meta = (AllowPrivateAccess = "true"))
		int32 CurrentHP;

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
		bool isAlive;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemyStats, meta = (AllowPrivateAccess = "true"))
		//const Type;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
