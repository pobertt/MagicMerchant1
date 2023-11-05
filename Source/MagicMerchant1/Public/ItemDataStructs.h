// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"

/**
 * 
 */
class MAGICMERCHANT1_API ItemDataStructs
{
public:
	ItemDataStructs();
	~ItemDataStructs();
};

UENUM()
enum class EItemQuality : uint8
{
	Common UMETA(DisplayName = "Common"),
	Uncommon UMETA(DisplayName = "Uncommon"),
	Rare UMETA(DisplayName = "Rare"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary")
};

UENUM()
enum class EItemType : uint8
{
	Ingredient UMETA(DisplayName = "Ingredient"),
	Potion UMETA(DisplayName = "Potion"),
	Magic UMETA(DisplayName = "Magic??"),
	Placeholder UMETA(DisplayName = "Placeholder")
};

USTRUCT()
struct FItemStatistics
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		float BuyValue;

	UPROPERTY(EditAnywhere)
		float SellValue;

	UPROPERTY(EditAnywhere)
		float DamageValue;
};

USTRUCT()
struct FItemTextData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		FText Name;

	UPROPERTY(EditAnywhere)
		FText Description;

	UPROPERTY(EditAnywhere)
		FText InteractionText;
	
	UPROPERTY(EditAnywhere)
		FText UsageText;
};

USTRUCT()
struct FItemNumericData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		float Weight;

	UPROPERTY(EditAnywhere)
		int32 MaxStackSize;

	UPROPERTY(EditAnywhere)
		bool bIsStackable;

};

USTRUCT()
struct FItemAssetData
{
	UPROPERTY(EditAnywhere)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
		UStaticMesh* Mesh;
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data")
		EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item Data")
		EItemType ItemQuality;

	UPROPERTY(EditAnywhere, Category = "Item Data")
		EItemType ItemStatistics;

	UPROPERTY(EditAnywhere, Category = "Item Data")
		EItemType TextData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
		EItemType NumericData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
		EItemType AssetData;
};