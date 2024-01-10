// Fill out your copyright notice in the Description page of Project Settings.


#include "BetterPlayerCharacter.h"

// Sets default values
ABetterPlayerCharacter::ABetterPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 100.0f;

	HealthRegen = 0.05f;

	HealthRate = 3.0f;

	mp = 100.0f;
	money = 0.0f;
	currency2 = 0.f;
	lvl = 1;

	//Combat Stats
	basicAttackDMG = 10;
	EnemyCounter = 0;
}

void ABetterPlayerCharacter::HealthRegenBar()
{
	if (Health < 100)
	{
		AddHp(HealthRegen);
		
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

void ABetterPlayerCharacter::MPRegenBar()
{
	if (mp < 100)
	{
		AddMp(0.05f);

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

float ABetterPlayerCharacter::AddMp(float AddMP)
{
	mp = mp + AddMP;
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
float ABetterPlayerCharacter::SubHp(int Dmg)
{
	Health = Health - Dmg;
	return Health;
}

float ABetterPlayerCharacter::SubMp(float MPCost)
{
	mp = mp - MPCost;

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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Enemy Made (MakeEnemyFunc)");
	if (bEnemyRespawn == true)
	{
		bEnemyRespawn = false;

		//SpawnActor BaseEnemy var Info
		FVector Location(0, 0, 0);
		FRotator Rotation(0, 0, 0);
		FActorSpawnParameters SpawnInfo;

		//Spawning a random enemy 
		SpawnNum = FMath::RandRange(1, 3);

		switch (SpawnNum)
		{
		case 1:
		{
			// AFireTypeEnemy* FireTypeEnemy = (GetWorld()->SpawnActor<AFireTypeEnemy>(Location, Rotation, SpawnInfo));
			BaseEnemyRef = (GetWorld()->SpawnActor<AFireTypeEnemy>(Location, Rotation, SpawnInfo));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "1");
			GameInstanceRef->SetEnemyUIType(SpawnNum);
		}
		break;
		case 2:
		{
			// AGrassTypeEnemy* GrassTypeEnemy = (GetWorld()->SpawnActor<AGrassTypeEnemy>(Location, Rotation, SpawnInfo));
			BaseEnemyRef = (GetWorld()->SpawnActor<AGrassTypeEnemy>(Location, Rotation, SpawnInfo));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "2");
			GameInstanceRef->SetEnemyUIType(SpawnNum);
			
		}
		break;
		case 3:
		{
			// AWaterTypeEnemy* WaterTypeEnemy = (GetWorld()->SpawnActor<AWaterTypeEnemy>(Location, Rotation, SpawnInfo));
			BaseEnemyRef = (GetWorld()->SpawnActor<AWaterTypeEnemy>(Location, Rotation, SpawnInfo));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "3"); 
			GameInstanceRef->SetEnemyUIType(SpawnNum);
			
		}
		break;
		default:
		{
			BaseEnemyRef = Cast<ABaseEnemy>(GetWorld()->SpawnActor<ABaseEnemy>(Location, Rotation, SpawnInfo));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Base Enemy");
			
		}
		break;
		}
		BaseEnemyRef->InitBaseEnemy(EnemyCounter);

		//Setting isAlive to true when made
		BaseEnemyRef->isAlive = true;

		if (BaseEnemyRef->isAlive == true && BaseEnemyRef->IsValidLowLevelFast()) {

			FTimerDelegate AttackPlayerDelegate;
			AttackPlayerDelegate.BindUFunction(this, "AttackPlayer", BaseEnemyRef->BaseAttack);

			GetWorld()->GetTimerManager().SetTimer(
				AttackPlayerTimerHandle,
				AttackPlayerDelegate,
				1.5f,
				true);
		}
	}
}

void ABetterPlayerCharacter::AttackEnemy(int Dmg, float MPCost, FString AttackType)
{
	if (BaseEnemyRef->isAlive == true && BaseEnemyRef->IsValidLowLevelFast()) {
		UE_LOG(LogTemp, Warning, TEXT("AttackEnemy function worked"));

		if (AttackType == "Fire") {
			this->GetComponentByClass<UMagicTypes>()->FireDmg(Dmg);

			MyFloat = BaseEnemyRef->CurrentHP - Dmg;
		}
		else if (AttackType == "Grass") {
			this->GetComponentByClass<UMagicTypes>()->GrassDmg(Dmg);

			MyFloat = BaseEnemyRef->CurrentHP - Dmg;
		}
		else if (AttackType == "Water") {
			this->GetComponentByClass<UMagicTypes>()->WaterDmg(Dmg);

			MyFloat = BaseEnemyRef->CurrentHP - Dmg;
		}
		else if (AttackType == "Normal") {
			MyFloat = BaseEnemyRef->CurrentHP - Dmg;
		}

		SubMp(MPCost);

		//Clamp??
		BaseEnemyRef->CurrentHP = FMath::Clamp(MyFloat, 0.0f, BaseEnemyRef->MaxHP);

		if (BaseEnemyRef->CurrentHP == 0)
		{
			//Kill the enemy if health is 0
			EnemyKilled();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Enemy Killed");
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Enemy Ref is not valid"));
	}
}

void ABetterPlayerCharacter::AttackPlayer(int Dmg)
{
	if (!BaseEnemyRef->IsValidLowLevel()) {
		AttackPlayerTimerHandle.Invalidate();
	}
	else if (BaseEnemyRef->isAlive == true && Health > 0) {
		SubHp(Dmg);
	}
	else if (Health <= 0) {
		AttackPlayerTimerHandle.Invalidate();
		PlayerDead();
	}
}

void ABetterPlayerCharacter::EnemyKilled()
{		
	//Set isAlive to false
	BaseEnemyRef->isAlive = false;

	//Give player however much money the enemy is worth
	AddMoney(BaseEnemyRef->Value);

	//Destroying the enemy when killed (so we dont have overlapping enemy spawns, only want 1 enemy at a time)
	BaseEnemyRef->Destroy();
		
	bEnemyRespawn = true;

	//If enemy is dead
	if (BaseEnemyRef->isAlive == false)
	{
		GetWorld()->GetTimerManager().SetTimer(
			EnemyRespawnTimerHandle,
			this,
			&ABetterPlayerCharacter::MakeEnemy,
			3.0f,
			false);

		// Increasing Enemy Counter
		EnemyCounter++;

		//Create a new enemy 
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Enemy Made (KilledFunc)");
	}

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
	GameInstanceRef = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	// GamemodeRef = Cast<AMagicMerchant1GameModeBase>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void ABetterPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HealthRegenBar();

	MPRegenBar();

}

// Called to bind functionality to input
void ABetterPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
