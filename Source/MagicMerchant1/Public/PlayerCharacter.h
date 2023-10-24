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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerStats, meta = (AllowPrivateAccess = "true"))
		int32 hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerStats, meta = (AllowPrivateAccess = "true"))
		int32 mp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerStats, meta = (AllowPrivateAccess = "true"))
		float money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerStats, meta = (AllowPrivateAccess = "true"))
		float currency2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerStats, meta = (AllowPrivateAccess = "true"))
		int32 lvl;

	//Declaring functions to add to player stats
	UFUNCTION(BlueprintCallable, Category = playerStats)
		int32 AddHp();

	UFUNCTION(BlueprintCallable, Category = playerStats)
		int32 AddMp();

	UFUNCTION(BlueprintCallable, Category = playerStats)
		float AddMoney();

	UFUNCTION(BlueprintCallable, Category = playerStats)
		float AddCurrency2();

	UFUNCTION(BlueprintCallable, Category = playerStats)
		int32 AddLvl();

	//Declaring functions to subtract from player stats
	UFUNCTION(BlueprintCallable, Category = playerStats)
		int32 SubHp();

	UFUNCTION(BlueprintCallable, Category = playerStats)
		int32 SubMp();

	UFUNCTION(BlueprintCallable, Category = playerStats)
		float SubMoney();

	UFUNCTION(BlueprintCallable, Category = playerStats)
		float SubCurrency2();

	UFUNCTION(BlueprintCallable, Category = playerStats)
		int32 SubLvl();

	UFUNCTION(BlueprintImplementableEvent, Category = playerStats)
		void SayHey();
	void SayHey_Implementation() { };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};

