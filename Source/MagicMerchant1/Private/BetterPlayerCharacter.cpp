// Fill out your copyright notice in the Description page of Project Settings.


#include "BetterPlayerCharacter.h"

// Sets default values
ABetterPlayerCharacter::ABetterPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	hp = 100;
	mp = 100;
	money = 10000.0f;
	currency2 = 0.f;
	lvl = 1;

	//Combat Stats
	basicAttackDMG = 10;
}

//Adding to player stats
int32 ABetterPlayerCharacter::AddHp()
{
	hp++;
	return hp;
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
	hp--;
	return hp;
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
	//Timer for making enemy does not work
	if (bEnemyRespawn == true)
	{
		bEnemyRespawn = false;

		//doesn't work
		GetWorld()->GetTimerManager().SetTimer(
			EnemyRespawnTimerHandle,
			this,
			&ABetterPlayerCharacter::EnemySpawnDelay,
			5.0f,
			false);

		//SpawnActor BaseEnemy var Info
		FVector Location(0, 0, 0);
		FRotator Rotation(0, 0, 0);
		FActorSpawnParameters SpawnInfo;

		if (!BaseEnemyRef->IsValidLowLevel())
		{
			//Creating new reference to Base Enemy
			//BaseEnemyRef = Cast<ABaseEnemy>(GetWorld()->SpawnActor<ABaseEnemy>(Location, Rotation, SpawnInfo));
			BaseEnemyRef = Cast<ABaseEnemy>(GetWorld()->SpawnActor<AFireTypeEnemy>(Location, Rotation, SpawnInfo));
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
		//BaseEnemyRef->Destroy();

		//calling enemy respawn
		EnemyRespawn();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Enemy Made");
}

void ABetterPlayerCharacter::EnemyRespawn()
{
		//If enemy is dead
		if (BaseEnemyRef->isAlive == false)
		{
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

void ABetterPlayerCharacter::EnemySpawnDelay()
{
	bEnemyRespawn = true;
	GetWorld()->GetTimerManager().ClearTimer(EnemyRespawnTimerHandle);
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

}

// Called to bind functionality to input
void ABetterPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//FMath::RandRange(1, 100)
