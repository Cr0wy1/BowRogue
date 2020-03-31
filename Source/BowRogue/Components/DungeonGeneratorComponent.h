// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameStructs.h"
#include "DungeonGeneratorComponent.generated.h"



class ADungeon;
class ADungeonRoom;
class ADungeonRoomEnd;




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWROGUE_API UDungeonGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDungeonGeneratorComponent();

protected:

	int32 longestPath = 0;
	FIntVector longestGridLoc;
	
	ADungeon* dungeon;

	//UPROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
		int32 seed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
		int32 roomGridRadius = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
		float roomSize = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	TSubclassOf<ADungeonRoom> spawnRoomBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	TSubclassOf<ADungeonRoomEnd> endRoomBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	TArray<TSubclassOf<ADungeonRoom>> dungeonRoomBPs;

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPrepareDungeon();

	void StartRoomGeneration();
	void PathMaker(FIntVector startPos, FIntVector dir, int32 length, int32 pathDistance, float accuracy = 1.0f);

	//returns true if room is succesfully setted
	bool SetGridRoom(const FIntVector &gridPos, int32 pathDistance, EGridRoomType gridtype = EGridRoomType::ROOM, ERoomType roomtype = ERoomType::FIGHT, bool bSpawnEntities = true);

	TSubclassOf<ADungeonRoom> GetRoomBPFromType(ERoomType roomType);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetSeed(int32 seed);

	//return a random rotation vector +90 or -90 rot
	FIntVector GetRandRotDirVector(const FIntVector &vec) const;
};
