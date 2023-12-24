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

	EnemyType = "Base";

	isAlive = false;
}

void ABaseEnemy::HealthRegen()
{
	if (CurrentHP < MaxHP)
	{
		CurrentHP = CurrentHP + 0.1f;
	}
}

void ABaseEnemy::InitBaseEnemy()
{
	MaxHP = MaxHP;
	CurrentHP = MaxHP;
	HPRegen = HPRegen;

	BaseAttack = BaseAttack;
	AttackMultiplier = AttackMultiplier;

	Defense = Defense;
	DefenseMultiplier = DefenseMultiplier;

	Value = 10;

	isAlive = false;
}

//These functions are for player combat spells, to know what type the enemy is

void ABaseEnemy::SetType(FString Type)
{
	EnemyType = Type;
}

FString ABaseEnemy::GetType()
{
	return EnemyType;
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	HealthRegen();
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AFireTypeEnemy::AFireTypeEnemy()
{
	SetType("Fire");

}

void AFireTypeEnemy::Tick(float DeltaTime)
{
	Super::BeginPlay();

	HealthRegen();
}

AGrassTypeEnemy::AGrassTypeEnemy()
{
	SetType("Grass");
}

void AGrassTypeEnemy::Tick(float DeltaTime)
{
	Super::BeginPlay();

	HealthRegen();
}

AWaterTypeEnemy::AWaterTypeEnemy()
{
	SetType("Water");
}

void AWaterTypeEnemy::Tick(float DeltaTime)
{
	Super::BeginPlay();

	HealthRegen();
}

