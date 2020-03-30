// Fill out your copyright notice in the Description page of Project Settings.


#include "StageActor.h"
#include "Dungeon.h"
#include "Engine/World.h"

// Sets default values
AStageActor::AStageActor(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStageActor::BeginPlay(){
	Super::BeginPlay();
	
}

void AStageActor::StartStage(){
	if (dungeonDefaultBP) {
		FVector dungeonLoc = GetActorLocation();
		for (size_t i = 0; i < 5; i++){

			ADungeon* spawnedDungeon = ADungeon::Construct(this, dungeonLoc, dungeonDefaultBP, i);
			dungeons.Add(spawnedDungeon);

			dungeonLoc += FVector(0, 0, 2000);
		}
	}
}

// Called every frame
void AStageActor::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

