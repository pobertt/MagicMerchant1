// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/MagicTypes.h"

// Sets default values for this component's properties
UMagicTypes::UMagicTypes()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMagicTypes::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMagicTypes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UMagicTypes::FireDmg(int Dmg)
{
	if (BaseEnemyRef->EnemyType == "Grass")
	{
		Dmg *= 2;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FormatAsNumber(Dmg));
	}
	else if (BaseEnemyRef->EnemyType == "Water") {
		Dmg *= 0.5;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::FormatAsNumber(Dmg));
	}
	else {
		Dmg *= 1;
	}
	return Dmg;
}

int UMagicTypes::GrassDmg(int Dmg)
{
	if (BaseEnemyRef->EnemyType == "Water")
	{
		Dmg *= 2;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::FormatAsNumber(Dmg));
	}
	else if (BaseEnemyRef->EnemyType == "Fire") {
		Dmg *= 0.5;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FormatAsNumber(Dmg));
	}
	else {
		Dmg *= 1;
	}
	return Dmg;
}

int UMagicTypes::WaterDmg(int Dmg)
{
	if (BaseEnemyRef->EnemyType == "Fire")
	{
		Dmg *= 2;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FormatAsNumber(Dmg));
	}
	else if (BaseEnemyRef->EnemyType == "Grass") {
		Dmg *= 0.5;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FormatAsNumber(Dmg));
	}
	else {
		Dmg *= 1;
	}
	return Dmg;
}