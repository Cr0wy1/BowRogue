// Fill out your copyright notice in the Description page of Project Settings.


#include "EntitySpawner.h"
#include "Entity.h"
#include "Engine/World.h"

// Sets default values
AEntitySpawner::AEntitySpawner(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//allowing spawner to have transforms, maybe remove this
	RootComponent = CreateDefaultSubobject<USceneComponent>("Scene");
}

// Called when the game starts or when spawned
void AEntitySpawner::BeginPlay(){
	Super::BeginPlay();
	
}

// Called every frame
void AEntitySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEntitySpawner::SpawnEntities(FSpawnPattern spawnPattern){
	
	int32 spawnNum = spawnPattern.spawns.Num();
	for (int32 i = 0; i < spawnNum; i++){
		spawnPattern[i].location += GetActorLocation();
		AEntity::Spawn(spawnPattern[i], this);
	}
}

void AEntitySpawner::AddSpawnedEntity(AEntity * spawnedEntity){
	spawnedEntities.AddUnique(spawnedEntity);
}

void AEntitySpawner::RemovedSpawnedEntity(AEntity * spawnedEntity){
	spawnedEntities.Remove(spawnedEntity);
	if (spawnedEntities.Num() <= 0) {
		OnAllEntitiesRemoved.Broadcast();
	}
}

AEntitySpawner * AEntitySpawner::Construct(AActor * owner, const FVector & Location){
	if (owner) {
		
		return owner->GetWorld()->SpawnActor<AEntitySpawner>(Location, FRotator::ZeroRotator);
	}
	return nullptr;
}

