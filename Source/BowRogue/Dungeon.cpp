// Fill out your copyright notice in the Description page of Project Settings.


#include "Dungeon.h"
#include "DungeonRoomEnd.h"
#include "PortalPlatform.h"

// Sets default values
ADungeon::ADungeon(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeon::BeginPlay(){
	Super::BeginPlay();
	
}

void ADungeon::OnLeaveDungeon(AActor * leavedActor, FVector destination){
	UE_LOG(LogTemp, Warning, TEXT("Leave Dungeon!"));

}

// Called every frame
void ADungeon::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void ADungeon::AddSpawnedRoom(ADungeonRoom * spawnedRoom){
	if (spawnedRoom) {
		ERoomType roomType = spawnedRoom->GetDungeonRoomParams().roomtype;
		
			switch (roomType){
				case ERoomType::SPAWN :
					roomSpawn = spawnedRoom;
					break;
				case ERoomType::END:
					roomEnd = Cast<ADungeonRoomEnd>(spawnedRoom);

					if (roomEnd) {
						roomEnd->GetPortal()->OnTeleport.AddDynamic(this, &ADungeon::OnLeaveDungeon);
					}

					break;

				default:
					roomBase.Add(spawnedRoom);
					break;
			}
	}
}

