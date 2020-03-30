// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemObject.h"
#include "Player/BowRogueCharacter.h"

UItemObject * UItemObject::Construct(UObject* owner, FItemData _itemData){

	if (!owner) { UE_LOG(LogTemp, Warning, TEXT("UItemObject::Construct: owner is nullptr")); return nullptr; }
	//if (!_itemData) { UE_LOG(LogTemp, Warning, TEXT("UItemObject::Construct: _itemData is nullptr")); return nullptr; }

	
	UItemObject* newItemObject = NewObject<UItemObject>(owner, _itemData.itemObjectBP);
	if (newItemObject) {
		newItemObject->itemData = _itemData;
	}
	

	return newItemObject;
}
