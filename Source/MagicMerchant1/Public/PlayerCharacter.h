// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class MAGICMERCHANT1_API APlayerCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerCharacter();
	
	//Player Stats
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = playerStats, meta = (AllowPrivateAccess = "true"))
	int hp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = playerStats, meta = (AllowPrivateAccess = "true"))
	int mp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerStats, meta = (AllowPrivateAccess = "true"))
	float money;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = playerStats, meta = (AllowPrivateAccess = "true"))
	float currency2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = playerStats, meta = (AllowPrivateAccess = "true"))
	int lvl;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};

