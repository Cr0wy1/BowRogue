// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGeneratorComponent.h"
#include "Dungeon/DungeonRoomEnd.h"
#include "Dungeon/Dungeon.h"
#include "AdvancedGameInstance.h"
#include "Assets/DungeonDefaultsAsset.h"

// Sets default values for this component's properties
UDungeonGeneratorComponent::UDungeonGeneratorComponent(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UDungeonGeneratorComponent::BeginPlay(){
	Super::BeginPlay();

	UAdvancedGameInstance* gameInstance = GetOwner()->GetGameInstance<UAdvancedGameInstance>();

	if (gameInstance) {
		UDungeonDefaultsAsset* dungeonDefaults = gameInstance->GetDungeonDefaultsAsset();

		if (!spawnRoomBP) {

			UE_LOG(LogTemp, Warning, TEXT("UDungeonGeneratorComponent: spawnRoomBP is empty"));
			spawnRoomBP = dungeonDefaults->roomDefault;

		}

		if (!endRoomBP) { 
			UE_LOG(LogTemp, Warning, TEXT("UDungeonGeneratorComponent: endRoomBP is empty"));
			endRoomBP = dungeonDefaults->roomEndDefault;
		}

		if (dungeonRoomBPs.Num() < 1 || !dungeonRoomBPs[0]) { 
			UE_LOG(LogTemp, Warning, TEXT("UDungeonGeneratorComponent: dungeonRoomBPs are empty"));
			dungeonRoomBPs.Add(dungeonDefaults->roomDefault);
		}
	}

	dungeon = Cast<ADungeon>(GetOwner());
	if (dungeon) {

		dungeon->OnPrepareDungeon.AddDynamic(this, &UDungeonGeneratorComponent::OnPrepareDungeon);
		///OnPrepareDungeon();

	}

}

void UDungeonGeneratorComponent::OnPrepareDungeon(){
	if (dungeon->GetStageActor()) {

		roomGridRadius = dungeon->GetStageLevel() + 1;

	}

	dungeon->gridRadius = roomGridRadius;


	SetSeed(seed);
	StartRoomGeneration();
	dungeon->grid.Log();
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
	dungeon->grid.Reset();
	dungeon->grid.Init(gridDel, gridDel);

	FIntVector cGridPos = FIntVector(roomGridRadius, roomGridRadius, 0);
	 
	SetGridRoom(cGridPos, 0, EGridRoomType::ROOM, ERoomType::SPAWN, false);


	for (int32 i = 0; i < 4; i++) {

		FIntVector randVDir = FGridDir::GetRandDir().GetVec();
		int32 randLength = FMath::Rand() % roomGridRadius;

		PathMaker(cGridPos, randVDir, randLength, 0, 0.7f);

	}

	//Set boss room at longest location
	//SetGridRoom(longestGridLoc, dungeon->grid[longestGridLoc.X][longestGridLoc.Y].pathDistance, EGridRoomType::ROOM, ERoomType::END, true);
	dungeon->grid[longestGridLoc.X][longestGridLoc.Y].roomtype = ERoomType::END;
	dungeon->grid[longestGridLoc.X][longestGridLoc.Y].roomBP = endRoomBP;



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
	//UE_LOG(LogTemp, Warning, TEXT("SetGridRoom"));

	if (dungeon->grid.IsValidIndex(gridPos.X, gridPos.Y)) {
		if (dungeon->grid[gridPos].gridtype == EGridRoomType::EMPTY) {

			dungeon->grid[gridPos].gridLoc = gridPos;
			dungeon->grid[gridPos].pathDistance = pathDistance;
			dungeon->grid[gridPos].gridtype = gridtype;
			dungeon->grid[gridPos].roomtype = roomtype;
			dungeon->grid[gridPos].bSpawnEntities = bSpawnEntities;
			dungeon->grid[gridPos].roomBP = GetRoomBPFromType(roomtype);

			if (pathDistance > longestPath) {
				longestPath = pathDistance;
				longestGridLoc = gridPos;
			}

			return true;
		}
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