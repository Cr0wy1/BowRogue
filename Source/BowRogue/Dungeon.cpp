// Fill out your copyright notice in the Description page of Project Settings.


#include "Dungeon.h"
#include "DungeonRoomEnd.h"
#include "PortalPlatform.h"
#include "StageActor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADungeon::ADungeon(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeon::BeginPlay(){
	Super::BeginPlay();
	
}

void ADungeon::Init(int32 _stageLevel){
	stageLevel = _stageLevel;
}

void ADungeon::OnEnterDungeon(){
	UE_LOG(LogTemp, Warning, TEXT("Enter Dungeon!"));

	
}

void ADungeon::OnLeaveDungeon(AActor * leavedActor, FVector destination){
	UE_LOG(LogTemp, Warning, TEXT("Leave Dungeon!"));
	nextDungeon->OnEnterDungeon();

	DestructDungeon();
}

ADungeon * ADungeon::Construct(AStageActor * _stageActor, FVector location, TSubclassOf<ADungeon> dungeonBP, int32 _stageLevel){

	ADungeon* dungeon = nullptr;

	if (_stageActor) {
		FTransform trans = FTransform(FRotator::ZeroRotator, location);
		dungeon = _stageActor->GetWorld()->SpawnActorDeferred<ADungeon>(dungeonBP, trans, _stageActor);
		dungeon->stageActor = _stageActor;
		dungeon->stageLevel = _stageLevel;
		UGameplayStatics::FinishSpawningActor(dungeon, trans);
	}

	return dungeon;
}

// Called every frame
void ADungeon::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void ADungeon::BuildDungeon(){

}

void ADungeon::DestructDungeon(){
	for (auto room : roomBase) {
		room->DestructRoom();
	}

	roomSpawn->DestructRoom();
	roomEnd->DestructRoom();
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

