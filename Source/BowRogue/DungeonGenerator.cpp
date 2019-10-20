// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGenerator.h"
#include "DungeonRoom.h"
#include "Engine/World.h"

// Sets default values
ADungeonGenerator::ADungeonGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeonGenerator::BeginPlay(){
	Super::BeginPlay();
	
	SetSeed(seed);
	StartRoomGeneration();
}

void ADungeonGenerator::StartRoomGeneration(){
	if (dungeonRoomBPs.Num() <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("ADungeonGenerator: dungeonRoomBPs Array is empty!"));
		return;
	}

	int32 gridDel = (roomGridRadius * 2) + 1;
	roomGrid.Init(TArray<EGridRoomType>(), gridDel);
	for (int32 i = 0; i < gridDel; i++){
		roomGrid[i].Init(EGridRoomType::EMPTY, gridDel);
	}
	
	FIntVector cGridPos = FIntVector(roomGridRadius, roomGridRadius, 0);
	
	SpawnRoom(cGridPos);

	for (int32 i = 0; i < 4; i++){
		
		FIntVector randVDir = vecDirs[i];
		int32 randLength = FMath::Rand() % roomGridRadius;

		PathMaker(cGridPos, randVDir, randLength, 0.7f);

	}

}

void ADungeonGenerator::PathMaker(FIntVector startPos, FIntVector dir, int32 length, float accuracy){
	
	FIntVector cPos = startPos;
	FIntVector cDir = dir;

	for (int32 i = 0; i < length; i++){

		if (SpawnRoom(cPos + cDir)) {
			cPos += cDir;
		}

		cDir = dir;
		if (FMath::FRand() > accuracy) {
			cDir = GetRandRotDirVector(cDir);
		}

		if (FMath::FRand() > 0.7f) {
			PathMaker(cPos, GetRandRotDirVector(cDir), length, 1);
		}
	}
}

bool ADungeonGenerator::SpawnRoom(const FIntVector &gridPos){
	if (roomGrid.IsValidIndex(gridPos.X) && roomGrid[0].IsValidIndex(gridPos.Y)) {
		if (roomGrid[gridPos.X][gridPos.Y] == EGridRoomType::EMPTY) {
			roomGrid[gridPos.X][gridPos.Y] = EGridRoomType::ROOM;

			FVector spawnLoc;
			spawnLoc.X = (roomSize + roomMargin) * (gridPos.X - roomGridRadius);
			spawnLoc.Y = (roomSize + roomMargin) * (gridPos.Y - roomGridRadius);
			spawnLoc.Z = 0;

			int32 iRandRoomBP = FMath::Rand() % dungeonRoomBPs.Num();
			GetWorld()->SpawnActor<ADungeonRoom>(dungeonRoomBPs[iRandRoomBP], spawnLoc, FRotator::ZeroRotator);

			++roomsPlaced;
			return true;
		}
	}

	return false;
}

// Called every frame
void ADungeonGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ADungeonGenerator::SetSeed(int32 seed){
	FMath::RandInit(seed);
}

FIntVector ADungeonGenerator::GetRandRotDirVector(const FIntVector & vec) const{
	FIntVector result;
	
	bool randBool = FMath::RandBool();

	if (vec.X == 0) {
		result.X = randBool ? 1 : -1;
		result.Y = 0;
	}
	else {
		result.X = 0;
		result.Y = randBool ? 1 : -1;
	}

	return result;
}

FIntVector ADungeonGenerator::GetRandGridDirVector() const{

	return vecDirs[FMath::Rand() % vecDirs.Num()];
}

