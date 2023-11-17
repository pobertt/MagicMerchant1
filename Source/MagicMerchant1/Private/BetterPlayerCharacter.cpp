// Fill out your copyright notice in the Description page of Project Settings.


#include "BetterPlayerCharacter.h"

// Sets default values
ABetterPlayerCharacter::ABetterPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	hp = 100;
	mp = 100;
	money = 0.f;
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

float ABetterPlayerCharacter::AddMoney()
{
	money++;
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

float ABetterPlayerCharacter::SubMoney()
{
	money--;
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
	//SpawnActor BaseEnemy var Info
	FVector Location(0, 0, 0);
	FRotator Rotation(0, 0, 0);
	FActorSpawnParameters SpawnInfo;

	//Creating new reference to Base Enemy
	BaseEnemyRef = Cast<ABaseEnemy>(GetWorld()->SpawnActor<ABaseEnemy>(Location, Rotation, SpawnInfo));

}

void ABetterPlayerCharacter::AttackEnemy()
{
	//when called minus enemy max hp by how much damage
	UE_LOG(LogTemp, Warning, TEXT("AttackEnemy function worked"));
	
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

