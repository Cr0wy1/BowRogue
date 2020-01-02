// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStructs.h"
#include "Entity.h"
#include "Item.h"
#include "Engine/StaticMesh.h"
#include "AttributeComponent.h"

//Init statics 
FIntVector FGridDir::FRONT_VEC = FIntVector(1, 0, 0);
FIntVector FGridDir::RIGHT_VEC = FIntVector(0, 1, 0);
FIntVector FGridDir::BACK_VEC = FIntVector(-1, 0, 0);
FIntVector FGridDir::LEFT_VEC = FIntVector(0, -1, 0);
FGridDir FGridDir::FRONT = FGridDir(EGridDir::FRONT);
FGridDir FGridDir::RIGHT = FGridDir(EGridDir::RIGHT);
FGridDir FGridDir::BACK = FGridDir(EGridDir::BACK);
FGridDir FGridDir::LEFT = FGridDir(EGridDir::LEFT);
TArray<FGridDir> FGridDir::DIRS = { FRONT, RIGHT, BACK, LEFT };

FGridDir::FGridDir(){
	SetDir(EGridDir::FRONT);
}

FGridDir::FGridDir(EGridDir griddir) {
	SetDir(griddir);
}


FGridDir FGridDir::RotateLeft(){
	switch (type){
	case EGridDir::FRONT:
		return FGridDir::LEFT;
	case EGridDir::RIGHT:
		return FGridDir::FRONT;
	case EGridDir::BACK:
		return FGridDir::RIGHT;
	case EGridDir::LEFT:
		return FGridDir::BACK;
	default:
		return EGridDir::FRONT;
	}
}

FGridDir FGridDir::RotateRight(){
	switch (type) {
	case EGridDir::FRONT:
		return FGridDir::RIGHT;
	case EGridDir::RIGHT:
		return FGridDir::BACK;
	case EGridDir::BACK:
		return FGridDir::LEFT;
	case EGridDir::LEFT:
		return FGridDir::FRONT;
	default:
		return EGridDir::FRONT;
	}
}

FGridDir FGridDir::Flip(){
	switch (type) {
	case EGridDir::FRONT:
		return FGridDir::BACK;
	case EGridDir::RIGHT:
		return FGridDir::LEFT;
	case EGridDir::BACK:
		return FGridDir::FRONT;
	case EGridDir::LEFT:
		return FGridDir::RIGHT;
	default:
		return EGridDir::FRONT;
	}
}

void FGridDir::SetDir(EGridDir griddir){
	type = griddir;
	switch (griddir) {
	case EGridDir::FRONT:
		vec = FIntVector(1, 0, 0);
		break;
	case EGridDir::RIGHT:
		vec = FIntVector(0, 1, 0);
		break;
	case EGridDir::BACK:
		vec = FIntVector(-1, 0, 0);
		break;
	case EGridDir::LEFT:
		vec = FIntVector(0, -1, 0);
		break;
	default:
		vec = FIntVector(1, 0, 0);
		type = EGridDir::FRONT;
		break;
	}
}

bool FGridDir::operator==(const FGridDir & other) const{
	return type == other.type;
}

//FItemData
FItemData * FItemData::FromId(UDataTable* datatable, FName id){

	FItemData* itemData = datatable->FindRow<FItemData>(id, FString());

	return itemData;
}


FAttribute::FAttribute(class UAttributeComponent* _attrComp, FName _name, float _min, float _max, float _value) : attrComp(_attrComp), name(_name), min(_min), max(_max), value(_value) {
}



void FAttribute::SetValue(float newValue){
	value = FMath::Clamp(newValue, min, max);
	NotifyAttributeComponent();
}

void FAttribute::SetMin(float newMin, bool updateValue){
	min = newMin > max ? max : newMin;
	if (updateValue && value < min) {
		value = min;
	}
	NotifyAttributeComponent();
}

void FAttribute::SetMax(float newMax, bool updateValue){
	max = newMax < min ? min : newMax;
	if (updateValue && value > max) {
		value = max;
	}
	NotifyAttributeComponent();
}

void FAttribute::NotifyAttributeComponent(){
	if (attrComp) {
		attrComp->OnAttributeUpdate(this);
	}
}

