// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonRoom.h"
#include "Entity.h"
#include "DungeonGenerator.h"
#include "Engine/World.h"
#include "EntitySpawner.h"
#include "RoomConnector.h"

// Sets default values
ADungeonRoom::ADungeonRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeonRoom::BeginPlay(){
	Super::BeginPlay();
	
	spawner = AEntitySpawner::Construct(this, GetActorLocation());
	if (spawner) {
		spawner->OnAllEntitiesRemoved.AddDynamic(this, &ADungeonRoom::OnAllEntitiesKilled);
		spawner->SpawnEntities(spawnPattern);
	}
}

void ADungeonRoom::OnAllEntitiesKilled(){
	OnRoomClear.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Room cleared!"));

}

void ADungeonRoom::Init(ADungeonGenerator * _dungeonGenerator, FIntVector _gridLoc){
	dungeonGenerator = _dungeonGenerator;
	gridLoc = _gridLoc;
}

// Called every frame
void ADungeonRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ADungeonRoom * ADungeonRoom::Construct(ADungeonGenerator * dungeonGenerator, TSubclassOf<ADungeonRoom> classBP, FVector location, FIntVector gridLoc){
	if (dungeonGenerator) {
		ADungeonRoom* spawnedRoom = dungeonGenerator->GetWorld()->SpawnActor<ADungeonRoom>(classBP, location, FRotator::ZeroRotator);
		spawnedRoom->Init(dungeonGenerator, gridLoc);
		return spawnedRoom;
	}
	return nullptr;
}

