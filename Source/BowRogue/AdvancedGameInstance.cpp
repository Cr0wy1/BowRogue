// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedGameInstance.h"
#include "WidgetAsset.h"
#include "DungeonGenerator.h"
#include "Engine/World.h"
#include "StructureAsset.h"

void UAdvancedGameInstance::Init(){
	Super::Init();

	if (dungeonGenerator_BP) {
		dungeonGenerator = GetWorld()->SpawnActor<ADungeonGenerator>(dungeonGenerator_BP);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AdvancedGameInstance: Missing dungeonGenerator_BP"));
	}
}
