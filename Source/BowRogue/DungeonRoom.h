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



UCLASS()
class BOWROGUE_API ADungeonRoom : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ADungeonRoom();

protected:
	
	FDungeonRoomParams params;

	UAdvancedGameInstance* gameInstance = nullptr;

	//UPROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TSubclassOf<ASpawningFloorActor> spawningFloorBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMesh* meshWall = nullptr;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	USceneComponent* sceneRootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* meshRoofComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* meshWall1Comp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* meshWall2Comp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* meshWall3Comp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* meshWall4Comp;



	ADungeonGenerator * dungeonGenerator;
	FIntVector gridLoc;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void BuildRoom();

public:	


	void Init(FIntVector _gridLoc, const FDungeonRoomParams &_params);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//return spawned Room, returns nullptr if dungeonGenerator is nullptr
	static ADungeonRoom* Construct(AActor* owner, TSubclassOf<ADungeonRoom> classBP, FVector location, FIntVector gridLoc, const FDungeonRoomParams &params = FDungeonRoomParams());

	void AddConnector(const FGridDir &dir);

	void AdjustRoomConnections();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ADungeon* TryGetDungeon();

	FORCEINLINE FIntVector GetGridLoc() const { return gridLoc; }
	FORCEINLINE ADungeonGenerator* GetDungeonGenerator() const { return dungeonGenerator; }
	FORCEINLINE FDungeonRoomParams GetDungeonRoomParams() const { return params; }
};
