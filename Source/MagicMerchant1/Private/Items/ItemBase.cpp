// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"

UItemBase::UItemBase()
{

}

UItemBase* UItemBase::CreateItemCopy() const
{
	//Creating a copy 
	UItemBase* ItemCopy = NewObject<UItemBase>(StaticClass());

	ItemCopy->ID = this->ID;
	ItemCopy->Quantity = this->Quantity;
	ItemCopy->ItemQuality = this->ItemQuality;
	ItemCopy->ItemType = this->ItemType;
	ItemCopy->TextData = this->TextData;
	ItemCopy->NumericData = this->NumericData;
	ItemCopy->ItemStatistics = this->ItemStatistics;
	ItemCopy->AssetData = this->AssetData;

	return ItemCopy;
}

void UItemBase::SetQuantity(const int32 NewQuantity)
{
	if (NewQuantity != Quantity)
	{
		//? what to do if true : what to do if false
		Quantity = FMath::Clamp(NewQuantity, 0, NumericData.bIsStackable ? NumericData.MaxStackSize : 1);

		// deleting item because you cant have 0 items
		//if (OwningInventory)
		//{
		//if(Quantity <= 0)
		//{
		//	OwningInventory->RemoveItem(this);
		//}
		//}
	}
}

void UItemBase::Use(ABetterPlayerCharacter* Character)
{

}