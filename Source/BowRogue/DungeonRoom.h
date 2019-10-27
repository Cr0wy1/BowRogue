// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStructs.h"
#include "DungeonRoom.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoomClear);

class AEntity;
class ADungeonGenerator;
class ARoomConnector;



UCLASS()
class BOWROGUE_API ADungeonRoom : public AActor
{
	GENERATED_BODY()
	
public:	

	bool bCanSpawnEntities = true;
	

	// Sets default values for this actor's properties
	ADungeonRoom();

protected:

	bool bIsClear = false;
	bool bIsOpen = false;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnParams")
	FSpawnPattern spawnPattern;

	ADungeonGenerator * dungeonGenerator;
	FIntVector gridLoc;

	class AEntitySpawner* spawner = nullptr;

	TMap<FGridDir, ARoomConnector*> connectors;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnAllEntitiesKilled();

public:	

	FOnRoomClear OnRoomClear;

	void Init(ADungeonGenerator * _dungeonGenerator, FIntVector _gridLoc);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//return spawned Room, returns nullptr if dungeonGenerator is nullptr
	static ADungeonRoom* Construct(ADungeonGenerator * dungeonGenerator, TSubclassOf<ADungeonRoom> classBP, FVector location, FIntVector gridLoc);

	void AddConnector(const FGridDir &dir, ARoomConnector* connector);

	void PrepareEnter();

	void SetOpen(bool isOpen);

	FORCEINLINE FIntVector GetGridLoc() const { return gridLoc; }
	FORCEINLINE ADungeonGenerator* GetDungeonGenerator() const { return dungeonGenerator; }
	FORCEINLINE bool IsClear() const { return bIsClear; }
	FORCEINLINE bool IsOpen() const { return bIsOpen; }
};
