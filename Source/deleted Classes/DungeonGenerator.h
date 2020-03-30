// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStructs.h"
#include "DungeonGenerator.generated.h"



class ADungeonRoom;



UCLASS()
class BOWROGUE_API ADungeonGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonGenerator();

protected:

	class UAdvancedGameInstance * gameInstance = nullptr;

	int32 longestPath = 0;
	FIntVector longestGridLoc;

	TArray<TArray<FGridRoom>> roomGrid;
	TMap<FIntVector, ADungeonRoom*> spawnedRooms;

	int32 roomsPlaced = 0;

	//UPROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	int32 seed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	int32 roomGridRadius = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	float roomSize = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	float roomMargin = 600.0f;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	TArray<TSubclassOf<ADungeonRoom>> dungeonRoomBPs;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 

	void StartRoomGeneration();
	void PathMaker(FIntVector startPos, FIntVector dir, int32 length, int32 pathDistance, float accuracy = 1.0f);

	//returns true if room is succesfully setted
	bool SetGridRoom(const FIntVector &gridPos, int32 pathDistance, EGridRoomType gridtype = EGridRoomType::ROOM, ERoomType roomtype = ERoomType::FIGHT, bool bSpawnEntities = true);

	//returns room if room spawned, else return nullptr
	ADungeonRoom* SpawnRooms();

	void LogGrid();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetSeed(int32 seed);
	 
	//return a random rotation vector +90 or -90 rot
	FIntVector GetRandRotDirVector(const FIntVector &vec) const;

	FORCEINLINE class UAdvancedGameInstance* GetAdvGameInstance() const { return gameInstance; }
	FORCEINLINE const TArray<TArray<FGridRoom>>* GetGridPtr() const { return &roomGrid; }
	FORCEINLINE class UStructureAsset* GetStructureAsset() const;
};
