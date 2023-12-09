// Fill out your copyright notice in the Description page of Project Settings.


#include "BetterPlayerCharacter.h"

// Sets default values
ABetterPlayerCharacter::ABetterPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 100.0f;

	HealthRegen = 0.5f;

	HealthRate = 3.0f;

	mp = 100;
	money = 10000.0f;
	currency2 = 0.f;
	lvl = 1;

	//Combat Stats
	basicAttackDMG = 10;
}

void ABetterPlayerCharacter::HealthRegenBar()
{
	if (Health < 100)
	{
		AddHp(0.1f);
		
		//Timer is not getting called
		//Health Regen and Health Rate are useless
		/*
		GetWorld()->GetTimerManager().SetTimer(
			HealthRateTimerHandle,
			this,
			&ABetterPlayerCharacter::HealthTimerReset,
			HealthRate,
			false);
		*/
	}
}

//Adding to player stats
float ABetterPlayerCharacter::AddHp(float AddHealth)
{
	Health = Health + AddHealth;
	return Health;
}

int32 ABetterPlayerCharacter::AddMp()
{
	mp++;
	return mp;
}

float ABetterPlayerCharacter::AddMoney(float Amount)
{
	money += Amount;
	return money;
}

float ABetterPlayerCharacter::AddCurrency2()
{
	currency2++;
	return currency2;
}

int32 ABetterPlayerCharacter::AddLvl()
{
	lvl++;
	return lvl;
}

//Subtracting from player stats
int32 ABetterPlayerCharacter::SubHp()
{
	Health = Health - 20;
	return Health;
}

int32 ABetterPlayerCharacter::SubMp()
{
	mp--;
	return mp;
}

float ABetterPlayerCharacter::SubMoney(int Cost)
{
	money -= Cost;
	return money;
}

float ABetterPlayerCharacter::SubCurrency2()
{
	currency2--;
	return currency2;
}

int32 ABetterPlayerCharacter::SubLvl()
{
	lvl--;
	return lvl;
}

void ABetterPlayerCharacter::MakeEnemy()
{

	if (bEnemyRespawn == true)
	{
		bEnemyRespawn = false;

		//SpawnActor BaseEnemy var Info
		FVector Location(0, 0, 0);
		FRotator Rotation(0, 0, 0);
		FActorSpawnParameters SpawnInfo;

		if (!BaseEnemyRef->IsValidLowLevel())
		{
			//Creating new reference to Enemy
			
			//Spawning a random enemy 
			int8 Num = FMath::RandRange(1, 3);

			switch (Num)
			{
			case 1:
				BaseEnemyRef = Cast<ABaseEnemy>(GetWorld()->SpawnActor<AFireTypeEnemy>(Location, Rotation, SpawnInfo));
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "1");
				break;
			case 2:
				BaseEnemyRef = Cast<ABaseEnemy>(GetWorld()->SpawnActor<AGrassTypeEnemy>(Location, Rotation, SpawnInfo));
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "2");
				break;
			case 3:
				BaseEnemyRef = Cast<ABaseEnemy>(GetWorld()->SpawnActor<AWaterTypeEnemy>(Location, Rotation, SpawnInfo));
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "3");
				break;
			default:
				BaseEnemyRef = Cast<ABaseEnemy>(GetWorld()->SpawnActor<ABaseEnemy>(Location, Rotation, SpawnInfo));
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Base Enemy");
				break;
			}
		}

		//Setting isAlive to true when made
		BaseEnemyRef->isAlive = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Enemy Made");
	}
}

void ABetterPlayerCharacter::AttackEnemy(int Dmg)
{
	UE_LOG(LogTemp, Warning, TEXT("AttackEnemy function worked"));

	//when called minus enemy current hp by how much damage
	MyFloat = BaseEnemyRef->CurrentHP - Dmg;

	//Clamp??
	BaseEnemyRef->CurrentHP = FMath::Clamp(MyFloat, 0.0f, BaseEnemyRef->MaxHP);
}

void ABetterPlayerCharacter::EnemyKilled()
{
		//Set isAlive to false
		BaseEnemyRef->isAlive = false;

		//Give player however much money the enemy is worth
		AddMoney(BaseEnemyRef->Value);

		//Destroying the enemy when killed (so we dont have overlapping enemy spawns, only want 1 enemy at a time)
		BaseEnemyRef->Destroy();

		//calling enemy respawn
		EnemyRespawn();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Enemy Made");

}

void ABetterPlayerCharacter::EnemyRespawn()
{
		//If enemy is dead
		if (BaseEnemyRef->isAlive == false)
		{
			bEnemyRespawn = true;

			//Setting things back to original value
			InitBaseEnemy();

			//Create a new enemy 
			MakeEnemy();
		}	
}

void ABetterPlayerCharacter::InitBaseEnemy()
{
	BaseEnemyRef->MaxHP = BaseEnemyRef->MaxHP;
	BaseEnemyRef->CurrentHP = BaseEnemyRef->MaxHP;
	BaseEnemyRef->HPRegen = BaseEnemyRef->HPRegen;

	BaseEnemyRef->BaseAttack = BaseEnemyRef->BaseAttack;
	BaseEnemyRef->AttackMultiplier = BaseEnemyRef->AttackMultiplier;

	BaseEnemyRef->Defense = BaseEnemyRef->Defense;
	BaseEnemyRef->DefenseMultiplier = BaseEnemyRef->DefenseMultiplier;

	BaseEnemyRef->Value = 10;

	BaseEnemyRef->isAlive = false;
}

//Not in use
void ABetterPlayerCharacter::EnemySpawnDelay()
{
	bEnemyRespawn = true;
	GetWorld()->GetTimerManager().ClearTimer(EnemyRespawnTimerHandle);
}

void ABetterPlayerCharacter::HealthTimerReset()
{
	GetWorld()->GetTimerManager().ClearTimer(HealthRateTimerHandle);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Health Timer Reset");
}

// Called when the game starts or when spawned
void ABetterPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SayHey();
}

// Called every frame
void ABetterPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HealthRegenBar();
}

// Called to bind functionality to input
void ABetterPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
