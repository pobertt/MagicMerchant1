// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class MAGICMERCHANT1_API AItem : public AActor
{
	GENERATED_BODY()
	//variables
	
public:	
	// Sets default values for this actor's properties
	AItem();
	FString name;
	FString description;
	float itemPrice;
	int32 numOfItem;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
