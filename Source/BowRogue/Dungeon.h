// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dungeon.generated.h"



class ADungeonRoom;
class ADungeonRoomEnd;
class AStageActor;



UCLASS()
class BOWROGUE_API ADungeon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeon();

protected:

	int32 stageLevel = 0;
	AStageActor* stageActor;

	ADungeonRoom * roomSpawn;
	ADungeonRoomEnd* roomEnd;
	TArray<ADungeonRoom*> roomBase;

	UPROPERTY(EditAnywhere)
	FVector spawnLocRelative;

	UPROPERTY(EditAnywhere)
	ADungeon* nextDungeon = nullptr;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Init(int32 _stageLevel);

	void OnEnterDungeon();

	UFUNCTION()
	void OnLeaveDungeon(AActor* leavedActor, FVector destination);

public:	

	static ADungeon* Construct(AStageActor* _stageActor, FVector location, TSubclassOf<ADungeon> dungeonBP, int32 _stageLevel);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BuildDungeon();
	void DestructDungeon();

	void AddSpawnedRoom(ADungeonRoom* spawnedRoom);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AStageActor* GetStageActor() const { return stageActor; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetStageLevel() const { return stageLevel; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FVector GetSpawnLocation() const { return GetActorLocation() + spawnLocRelative; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ADungeon* GetNextDungeon() { return nextDungeon; }
};
