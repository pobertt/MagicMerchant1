// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseEnemy.h"
#include "MagicTypes.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICMERCHANT1_API UMagicTypes : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMagicTypes();

	//Base Enemy Reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class ABaseEnemy* BaseEnemyRef;

	int FireDmg(int Dmg);

	int GrassDmg(int Dmg);

	int WaterDmg(int Dmg);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
