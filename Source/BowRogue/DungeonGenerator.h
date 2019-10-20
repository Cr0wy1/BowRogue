// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.generated.h"



UENUM()
enum class EGridRoomType : uint8 {

	EMPTY, //Room can be placed
	DUMMY, //Room without door connection
	ROOM //Room with door connection

};


UCLASS()
class BOWROGUE_API ADungeonGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonGenerator();

protected:

	TArray<TArray<EGridRoomType>> roomGrid;
	int32 roomsPlaced = 0;

	TArray<FIntVector> vecDirs = { FIntVector(1, 0, 0), FIntVector(0, 1, 0), FIntVector(-1, 0, 0), FIntVector(0, -1, 0) };

	//UPROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	int32 seed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	int32 roomGridRadius = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	float roomSize = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	float roomMargin = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	TArray<TSubclassOf<class ADungeonRoom>> dungeonRoomBPs;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void StartRoomGeneration();
	void PathMaker(FIntVector startPos, FIntVector dir, int32 length, float accuracy = 1.0f);

	//returns true if room spawned
	bool SpawnRoom(const FIntVector &gridPos);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetSeed(int32 seed);

	//return a random rotation vector +90 or -90 rot
	FIntVector GetRandRotDirVector(const FIntVector &vec) const;

	//returns a random Vector(up, bottom, right or left)
	FIntVector GetRandGridDirVector() const;

};
