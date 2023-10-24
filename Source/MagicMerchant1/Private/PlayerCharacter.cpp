// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	hp = 100;
	mp = 100;
	money = 0.f;
	currency2 = 0.f;
	lvl = 1;
}

//Adding to player stats
int32 APlayerCharacter::AddHp()
{
	hp++;
	return hp;
}

int32 APlayerCharacter::AddMp()
{
	mp++;
	return mp;
}

float APlayerCharacter::AddMoney()
{
	money++;
	return money;
}

float APlayerCharacter::AddCurrency2()
{
	currency2++;
	return currency2;
}

int32 APlayerCharacter::AddLvl()
{
	lvl++;
	return lvl;
}

//Subtracting from player stats
int32 APlayerCharacter::SubHp()
{
	hp--;
	return hp;
}

int32 APlayerCharacter::SubMp()
{
	mp--;
	return mp;
}

float APlayerCharacter::SubMoney()
{
	money--;
	return money;
}

float APlayerCharacter::SubCurrency2()
{
	currency2--;
	return currency2;
}

int32 APlayerCharacter::SubLvl()
{
	lvl--;
	return lvl;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SayHey();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



