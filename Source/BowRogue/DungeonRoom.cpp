// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonRoom.h"
#include "Entity.h"
#include "DungeonGenerator.h"
#include "Engine/World.h"
#include "EntitySpawner.h"
#include "RoomConnector.h"
#include "Kismet/GameplayStatics.h"
#include "StructureAsset.h"

// Sets default values
ADungeonRoom::ADungeonRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeonRoom::BeginPlay(){
	Super::BeginPlay();
	

}

void ADungeonRoom::OnAllEntitiesKilled(){
	bIsClear = true;
	bIsOpen = true;
	OnRoomClear.Broadcast();
	//UE_LOG(LogTemp, Warning, TEXT("Room cleared!"));

}

void ADungeonRoom::Init(ADungeonGenerator * _dungeonGenerator, FIntVector _gridLoc, const FDungeonRoomParams &_params){
	dungeonGenerator = _dungeonGenerator;
	gridLoc = _gridLoc;
	params = _params;

	if (!params.bSpawnEntities) {

		bIsClear = true;
		bIsOpen = true;
	}
}

// Called every frame
void ADungeonRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ADungeonRoom * ADungeonRoom::Construct(ADungeonGenerator * dungeonGenerator, TSubclassOf<ADungeonRoom> classBP, FVector location, FIntVector gridLoc, const FDungeonRoomParams &params){
	if (dungeonGenerator) {
		FTransform spawnTrans;
		spawnTrans.SetLocation(location);
		spawnTrans.SetRotation(FQuat::Identity);

		UStructureAsset* structureAsset = dungeonGenerator->GetStructureAsset();
		if (structureAsset && structureAsset->bossPortal_BP) {
			if (params.roomtype == ERoomType::BOSS) {
				dungeonGenerator->GetWorld()->SpawnActor<AActor>(structureAsset->bossPortal_BP, location, FRotator::ZeroRotator);
			}
		}

		ADungeonRoom* spawnedRoom = dungeonGenerator->GetWorld()->SpawnActorDeferred<ADungeonRoom>(classBP, spawnTrans, dungeonGenerator);
		//ADungeonRoom* spawnedRoom = dungeonGenerator->GetWorld()->SpawnActor<ADungeonRoom>(classBP, location, FRotator::ZeroRotator);
		spawnedRoom->Init(dungeonGenerator, gridLoc, params);

		UGameplayStatics::FinishSpawningActor(spawnedRoom, spawnTrans);

		return spawnedRoom;
	}
	return nullptr;
}

void ADungeonRoom::AddConnector(const FGridDir & dir, ARoomConnector * connector){
	connectors.Add(dir, connector);
}

void ADungeonRoom::PrepareEnter(){
	spawner = AEntitySpawner::Construct(this, GetActorLocation());
	if (spawner) {
		spawner->OnAllEntitiesRemoved.AddDynamic(this, &ADungeonRoom::OnAllEntitiesKilled);
		spawner->SpawnEntities(spawnPattern);
	}
}

void ADungeonRoom::SetOpen(bool isOpen){
	bIsOpen = isOpen;
}

