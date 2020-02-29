// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGeneratorComponent.h"
#include "DungeonRoomEnd.h"
#include "Dungeon.h"

// Sets default values for this component's properties
UDungeonGeneratorComponent::UDungeonGeneratorComponent(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UDungeonGeneratorComponent::BeginPlay(){
	Super::BeginPlay();

	if (!spawnRoomBP) { UE_LOG(LogTemp, Warning, TEXT("UDungeonGeneratorComponent: spawnRoomBP is empty")); return; }
	if (!endRoomBP) { UE_LOG(LogTemp, Warning, TEXT("UDungeonGeneratorComponent: endRoomBP is empty")); return; }
	if (dungeonRoomBPs.Num() < 1 || !dungeonRoomBPs[0]) { UE_LOG(LogTemp, Warning, TEXT("UDungeonGeneratorComponent: dungeonRoomBPs are empty")); return; }

	SetSeed(seed);
	StartRoomGeneration();
	SpawnRooms();
}


// Called every frame
void UDungeonGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UDungeonGeneratorComponent::StartRoomGeneration() {
	if (dungeonRoomBPs.Num() <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("ADungeonGenerator: dungeonRoomBPs Array is empty!"));
		return;
	}

	int32 gridDel = (roomGridRadius * 2) + 1;
	roomGrid.Init(TArray<FGridRoom>(), gridDel);
	for (int32 i = 0; i < gridDel; i++) {
		roomGrid[i].Init(FGridRoom(), gridDel);
	}

	FIntVector cGridPos = FIntVector(roomGridRadius, roomGridRadius, 0);

	SetGridRoom(cGridPos, 0, EGridRoomType::ROOM, ERoomType::SPAWN, false);


	for (int32 i = 0; i < 4; i++) {

		FIntVector randVDir = FGridDir::GetRandDir().GetVec();
		int32 randLength = FMath::Rand() % roomGridRadius;

		PathMaker(cGridPos, randVDir, randLength, 0, 0.7f);

	}

	//Set boss room at longest location
	roomGrid[longestGridLoc.X][longestGridLoc.Y].roomtype = ERoomType::END;



	//LogGrid();
}

void UDungeonGeneratorComponent::PathMaker(FIntVector startPos, FIntVector dir, int32 length, int32 pathDistance, float accuracy) {

	FIntVector cPos = startPos;
	FIntVector cDir = dir;

	for (int32 i = 0; i < length; i++) {

		if (SetGridRoom(cPos + cDir, pathDistance + 1)) {
			cPos += cDir;
			pathDistance++;
		}

		cDir = dir;
		if (FMath::FRand() > accuracy) {
			cDir = GetRandRotDirVector(cDir);
		}

		if (FMath::FRand() > 0.7f) {
			PathMaker(cPos, GetRandRotDirVector(cDir), length, pathDistance, 1);
		}
	}
}

bool UDungeonGeneratorComponent::SetGridRoom(const FIntVector & gridPos, int32 pathDistance, EGridRoomType gridtype, ERoomType roomtype, bool bSpawnEntities) {
	if (roomGrid.IsValidIndex(gridPos.X) && roomGrid[0].IsValidIndex(gridPos.Y)) {
		if (roomGrid[gridPos.X][gridPos.Y].gridtype == EGridRoomType::EMPTY) {

			roomGrid[gridPos.X][gridPos.Y].pathDistance = pathDistance;
			roomGrid[gridPos.X][gridPos.Y].gridtype = gridtype;
			roomGrid[gridPos.X][gridPos.Y].roomtype = roomtype;
			roomGrid[gridPos.X][gridPos.Y].bSpawnEntities = bSpawnEntities;

			if (pathDistance > longestPath) {
				longestPath = pathDistance;
				longestGridLoc = gridPos;
			}

			return true;
		}
	}

	return false;
}

void UDungeonGeneratorComponent::SpawnRooms() {

	for (int32 x = 0; x < roomGrid.Num(); x++) {
		for (int32 y = 0; y < roomGrid[x].Num(); y++) {

			if (roomGrid[x][y].gridtype != EGridRoomType::EMPTY) {
				FVector spawnLoc;
				spawnLoc.X = roomSize * (x - roomGridRadius);
				spawnLoc.Y = roomSize * (y - roomGridRadius);
				
				spawnLoc.Z = GetOwner()->GetActorLocation().Z;

				ADungeonRoom* spawnedRoom = ADungeonRoom::Construct(GetOwner(), GetRoomBPFromType(roomGrid[x][y].roomtype), spawnLoc, FIntVector(x, y, 0), roomGrid[x][y]);

				spawnedRooms.Add(FIntVector(x, y, 0), spawnedRoom);
				CheckConnectors(spawnedRoom, FIntVector(x, y, 0));

				++roomsPlaced;
			}


		}
	}
}

bool UDungeonGeneratorComponent::CheckConnectors(ADungeonRoom* cRoom, const FIntVector & gridPos) {
	//UE_LOG(LogTemp, Warning, TEXT("checkGrid %s"), *gridPos.ToString());

	ADungeonRoom** frontRoom = spawnedRooms.Find(gridPos + FGridDir::FRONT_VEC);
	if (frontRoom) {
		(*frontRoom)->AddConnector(FGridDir::BACK);
		cRoom->AddConnector(FGridDir::FRONT);
	}

	ADungeonRoom** rightRoom = spawnedRooms.Find(gridPos + FGridDir::RIGHT_VEC);
	if (rightRoom) {
		(*rightRoom)->AddConnector(FGridDir::LEFT);
		cRoom->AddConnector(FGridDir::RIGHT);
	}

	ADungeonRoom** backRoom = spawnedRooms.Find(gridPos + FGridDir::BACK_VEC);
	if (backRoom) {
		(*backRoom)->AddConnector(FGridDir::FRONT);
		cRoom->AddConnector(FGridDir::BACK);
	}

	ADungeonRoom** leftRoom = spawnedRooms.Find(gridPos + FGridDir::LEFT_VEC);
	if (leftRoom) {
		(*leftRoom)->AddConnector(FGridDir::RIGHT);
		cRoom->AddConnector(FGridDir::LEFT);
	}

	return false;
}

TSubclassOf<ADungeonRoom> UDungeonGeneratorComponent::GetRoomBPFromType(ERoomType roomType){

	switch (roomType){

	case ERoomType::SPAWN:
		return spawnRoomBP;

	case ERoomType::END:
		return endRoomBP;
	}
	int32 iRandRoomBP = FMath::Rand() % dungeonRoomBPs.Num();
	return dungeonRoomBPs[iRandRoomBP];
}

void UDungeonGeneratorComponent::LogGrid() {
	if (roomGrid.Num() < 1 && roomGrid[0].Num() < 1) return;

	int32 gridSizeX = roomGrid.Num();
	int32 gridSizeY = roomGrid[0].Num();

	for (int32 x = gridSizeX - 1; x >= 0; x--) {
		FString row = "";
		for (int32 y = 0; y < gridSizeY; y++) {
			if (roomGrid[x][y].gridtype != EGridRoomType::EMPTY) {
				row += FString::FromInt(roomGrid[x][y].pathDistance);
			}
			else {
				row += "O";
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *row);

	}
}

void UDungeonGeneratorComponent::SetSeed(int32 seed) {
	FMath::RandInit(seed);
}

FIntVector UDungeonGeneratorComponent::GetRandRotDirVector(const FIntVector & vec) const {
	FIntVector result;
	result.Z = 0;

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