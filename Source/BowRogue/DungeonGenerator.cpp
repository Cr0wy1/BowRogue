// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGenerator.h"
#include "DungeonRoom.h"
#include "Engine/World.h"
#include "RoomConnector.h"
#include "AdvancedGameInstance.h"

// Sets default values
ADungeonGenerator::ADungeonGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeonGenerator::BeginPlay(){
	Super::BeginPlay();


	gameInstance = GetGameInstance<UAdvancedGameInstance>();
	
	if (gameInstance) {
		SetSeed(seed);
		StartRoomGeneration();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("DungeonGenerator BeginPlay(): gameInstance is nullptr"));
	}

}

void ADungeonGenerator::StartRoomGeneration(){
	if (dungeonRoomBPs.Num() <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("ADungeonGenerator: dungeonRoomBPs Array is empty!"));
		return;
	}

	int32 gridDel = (roomGridRadius * 2) + 1;
	roomGrid.Init(TArray<FGridRoom>(), gridDel);
	for (int32 i = 0; i < gridDel; i++){
		roomGrid[i].Init(FGridRoom(), gridDel);
	}
	
	FIntVector cGridPos = FIntVector(roomGridRadius, roomGridRadius, 0);
	
	SetGridRoom(cGridPos, 0, EGridRoomType::ROOM, ERoomType::SPAWN, false);


	for (int32 i = 0; i < 4; i++){
		
		FIntVector randVDir = FGridDir::GetRandDir().GetVec();
		int32 randLength = FMath::Rand() % roomGridRadius;

		PathMaker(cGridPos, randVDir, randLength, 0, 0.7f);

	}

	//Set boss room at longest location
	roomGrid[longestGridLoc.X][longestGridLoc.Y].roomtype = ERoomType::BOSS;

	SpawnRooms();

	//LogGrid();
}

void ADungeonGenerator::PathMaker(FIntVector startPos, FIntVector dir, int32 length, int32 pathDistance, float accuracy){
	
	FIntVector cPos = startPos;
	FIntVector cDir = dir;

	for (int32 i = 0; i < length; i++){

		if (SetGridRoom(cPos + cDir, pathDistance+1)) {
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

bool ADungeonGenerator::SetGridRoom(const FIntVector & gridPos, int32 pathDistance, EGridRoomType gridtype, ERoomType roomtype, bool bSpawnEntities){
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

ADungeonRoom* ADungeonGenerator::SpawnRooms(){

	for (int32 x = 0; x < roomGrid.Num(); x++){
		for (int32 y = 0; y < roomGrid[x].Num(); y++) {

			if (roomGrid[x][y].gridtype != EGridRoomType::EMPTY) {
				FVector spawnLoc;
				spawnLoc.X = (roomSize + roomMargin) * (x - roomGridRadius);
				spawnLoc.Y = (roomSize + roomMargin) * (y - roomGridRadius);
				spawnLoc.Z = 0;

				int32 iRandRoomBP = FMath::Rand() % dungeonRoomBPs.Num();
				ADungeonRoom* spawnedRoom = ADungeonRoom::Construct(this, dungeonRoomBPs[iRandRoomBP], spawnLoc, FIntVector(x, y, 0), roomGrid[x][y]);

				spawnedRooms.Add(FIntVector(x, y, 0), spawnedRoom);
				//CheckConnectors(spawnedRoom, FIntVector(x, y, 0));

				++roomsPlaced;
			}


		}
	}

	return nullptr;
}

bool ADungeonGenerator::CheckConnectors(ADungeonRoom* cRoom, const FIntVector & gridPos){
	//UE_LOG(LogTemp, Warning, TEXT("checkGrid %s"), *gridPos.ToString());

	ADungeonRoom** frontRoom = spawnedRooms.Find(gridPos + FGridDir::FRONT_VEC);
	if (frontRoom) {
		ARoomConnector* connector = ARoomConnector::Construct(roomConnectorBP, cRoom, *frontRoom);
		(*frontRoom)->AddConnector(FGridDir::BACK, connector);
		cRoom->AddConnector(FGridDir::FRONT, connector);
	}

	ADungeonRoom** rightRoom = spawnedRooms.Find(gridPos + FGridDir::RIGHT_VEC);
	if (rightRoom) {
		ARoomConnector* connector = ARoomConnector::Construct(roomConnectorBP, cRoom, *rightRoom);
		(*rightRoom)->AddConnector(FGridDir::LEFT, connector);
		cRoom->AddConnector(FGridDir::RIGHT, connector);
	}

	ADungeonRoom** backRoom = spawnedRooms.Find(gridPos + FGridDir::BACK_VEC);
	if (backRoom) {
		ARoomConnector* connector = ARoomConnector::Construct(roomConnectorBP, cRoom, *backRoom);
		(*backRoom)->AddConnector(FGridDir::FRONT, connector);
		cRoom->AddConnector(FGridDir::BACK, connector);
	}

	ADungeonRoom** leftRoom = spawnedRooms.Find(gridPos + FGridDir::LEFT_VEC);
	if (leftRoom) {
		ARoomConnector* connector = ARoomConnector::Construct(roomConnectorBP, cRoom, *leftRoom);
		(*leftRoom)->AddConnector(FGridDir::RIGHT, connector);
		cRoom->AddConnector(FGridDir::LEFT, connector);
	}

	return false;
}

void ADungeonGenerator::LogGrid(){
	if (roomGrid.Num() < 1 && roomGrid[0].Num() < 1) return;

	int32 gridSizeX = roomGrid.Num();
	int32 gridSizeY = roomGrid[0].Num();

	for (int32 x = gridSizeX - 1; x >= 0; x--) {
		FString row = "";
		for (int32 y = 0; y < gridSizeY; y++) {
			if (roomGrid[x][y].gridtype != EGridRoomType::EMPTY) {
				row += FString::FromInt( roomGrid[x][y].pathDistance );
			}
			else {
				row += "O";
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *row);

	}
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

UStructureAsset * ADungeonGenerator::GetStructureAsset() const
{
	return gameInstance ? gameInstance->GetStructureAsset() : nullptr;
}

