// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStructs.h"
#include "DungeonRoom.generated.h"



class ADungeon;
class ADungeonGenerator;
class ASpawningFloorActor;
class UAdvancedGameInstance;
class ARoomPartRoof;
class ARoomPartWall;
class ARoomPartPillar;



USTRUCT()
struct  BOWROGUE_API FRoomWalls {
	GENERATED_BODY()

	ARoomPartWall* front = nullptr;
	ARoomPartWall* right = nullptr;
	ARoomPartWall* back = nullptr;
	ARoomPartWall* left = nullptr;
};


UCLASS()
class BOWROGUE_API ADungeonRoom : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ADungeonRoom();

protected:
	
	FDungeonRoomParams params;
	FConnectedRooms connectedRooms;

	UAdvancedGameInstance* gameInstance = nullptr;

	//UPROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parts")
	TSubclassOf<ASpawningFloorActor> spawningFloorBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parts")
	TSubclassOf<ARoomPartRoof> roofBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parts")
	TSubclassOf<ARoomPartWall> wallBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parts")
	TSubclassOf<ARoomPartPillar> pillarBP;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	USceneComponent* sceneRootComp;

	ADungeonGenerator * dungeonGenerator;
	FIntVector gridLoc;

	FRoomWalls walls;
	ARoomPartRoof* roof;
	ASpawningFloorActor* floor;
	TArray<ARoomPartPillar*> pillars;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	

public:	


	void Init(FIntVector _gridLoc, const FDungeonRoomParams &_params);

	void BuildRoom(FConnectedRooms _connectedRooms);
	void DestructRoom();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//return spawned Room, returns nullptr if dungeonGenerator is nullptr
	static ADungeonRoom* Construct(AActor* owner, TSubclassOf<ADungeonRoom> classBP, FVector location, FIntVector gridLoc, const FDungeonRoomParams &params = FDungeonRoomParams());


	UFUNCTION(BlueprintCallable)
	FORCEINLINE ADungeon* TryGetDungeon();

	FORCEINLINE FIntVector GetGridLoc() const { return gridLoc; }
	FORCEINLINE ADungeonGenerator* GetDungeonGenerator() const { return dungeonGenerator; }
	FORCEINLINE FDungeonRoomParams GetDungeonRoomParams() const { return params; }
};
