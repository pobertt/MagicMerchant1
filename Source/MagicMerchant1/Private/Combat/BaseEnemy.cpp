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

	Value = 25;

	EnemyType = "Base";

	isAlive = true;

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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "init base enemy called");

	MaxHP = MaxHP;
	CurrentHP = MaxHP;
	HPRegen = HPRegen;

	AttackMultiplier = AttackMultiplier;

	BaseAttack = BaseAttack;

	Value = 25;

	isAlive = true;
	// isAlive = false;

	EnemyCounter = EnemyCounter + counter;

	if (EnemyCounter < 1) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "not upgraded");
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "ENEMY UPGRADED");
		EnemyUpgrade();
	}
}

void ABaseEnemy::EnemyUpgrade()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "EnemyUpgrade(FunctionCalled)");

	MaxHP = MaxHP + (1.5 * EnemyCounter);
	CurrentHP = CurrentHP + (1.5 * EnemyCounter);
	HPRegen = HPRegen + (HPRegen * EnemyCounter);
	
	AttackMultiplier = AttackMultiplier + (0.5 * EnemyCounter);

	BaseAttack = BaseAttack * AttackMultiplier;

	Value = Value + (1.5 * EnemyCounter);
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

	if (CurrentHP > 0) HealthRegen();

	if (isAlive == false) {
		Destroy();
	}
}

AGrassTypeEnemy::AGrassTypeEnemy()
{
	SetType("Grass");
}

void AGrassTypeEnemy::Tick(float DeltaTime)
{
	Super::BeginPlay();

	if (CurrentHP > 0) HealthRegen();

	if (isAlive == false) {
		Destroy();
	}
}

AWaterTypeEnemy::AWaterTypeEnemy()
{
	SetType("Water");
}

void AWaterTypeEnemy::Tick(float DeltaTime)
{
	Super::BeginPlay();

	if (CurrentHP > 0) HealthRegen();

	if (isAlive == false) {
		Destroy();
	}
}

