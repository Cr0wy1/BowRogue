// Fill out your copyright notice in the Description page of Project Settings.


#include "EntitySpawnerComponent.h"
#include "Entity/Entity.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UEntitySpawnerComponent::UEntitySpawnerComponent(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEntitySpawnerComponent::BeginPlay(){
	Super::BeginPlay();

	
}


void UEntitySpawnerComponent::StartSpawning(){

	//For each Params in array
	for (auto spawnParams : spawnParamsArray) {

		if (spawnParams.entitySpawns.Num() > 0) {
			//For each repeat in params
			for (int32 i = 0; i < spawnParams.repeats; i++) {
				for (auto spawnEntity : spawnParams.entitySpawns) {
					spawnQueue.Enqueue(spawnEntity);
				}
			}
		}

	}

}

// Called every frame
void UEntitySpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetWorld()->GetTimeSeconds() >= nextSpawnTime && !spawnQueue.IsEmpty()) {
		FEntitySpawn entitySpawn;
		spawnQueue.Dequeue(entitySpawn);

		AEntity* spawnedEntitiy = GetWorld()->SpawnActor<AEntity>(entitySpawn.entityBP, GetComponentLocation(), FRotator::ZeroRotator);

		nextSpawnTime = GetWorld()->GetTimeSeconds() + entitySpawn.delayToNextEntity;
	}
}

