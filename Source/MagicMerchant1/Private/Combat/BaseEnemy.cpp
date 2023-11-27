// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/BaseEnemy.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Base Enemy Stats
	MaxHP = 100;
	CurrentHP = MaxHP;
	HPRegen = 0.5f;

	BaseAttack = 10;
	AttackMultiplier = 1;

	Defense = 0;
	DefenseMultiplier = 1;

	Value = 10;

	isAlive = false;
}

void ABaseEnemy::ResetHealth()
{
	//CurrentHP = MaxHP;
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AFireTypeEnemy::AFireTypeEnemy()
{
	MaxHP = 150;
	CurrentHP = MaxHP;

}

AGrassTypeEnemy::AGrassTypeEnemy()
{

}

AWaterTypeEnemy::AWaterTypeEnemy()
{

}
