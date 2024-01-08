// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/BaseEnemy.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Base Enemy Stats
	MaxHP = 20;
	CurrentHP = MaxHP;
	HPRegen = 0.0005f;

	BaseAttack = 5;
	AttackMultiplier = 2;

	Value = 10;

	EnemyType = "Base";

	isAlive = false;

	EnemyCounter = 0;

}

void ABaseEnemy::HealthRegen()
{
	if (CurrentHP < MaxHP)
	{
		CurrentHP = CurrentHP + HPRegen;
	}
}

void ABaseEnemy::InitBaseEnemy(int32 counter)
{
	EnemyCounter += counter;

	MaxHP = MaxHP;
	CurrentHP = MaxHP;
	HPRegen = HPRegen;

	BaseAttack = BaseAttack;
	AttackMultiplier = AttackMultiplier;

	Value = 10;

	isAlive = false;

	if (EnemyCounter < 5) {
		
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "ENEMY UPGRADED");
		EnemyUpgrade();
	}
}

void ABaseEnemy::EnemyUpgrade()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "EnemyUPgrade(FunctionCalled)");
	BaseAttack = BaseAttack * AttackMultiplier;

	MaxHP = MaxHP + 5;
	CurrentHP = MaxHP + 5;
	HPRegen = HPRegen + 5;

	Value = 10000;

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

