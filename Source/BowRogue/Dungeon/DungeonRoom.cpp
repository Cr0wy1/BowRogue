// Fill out your copyright notice in the Description page of Project Settings.


#include "Dungeon/DungeonRoom.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Assets/StructureAsset.h"
#include "AdvancedGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Dungeon/SpawningFloorActor.h"
#include "Dungeon/Dungeon.h"
#include "Dungeon/RoomPartRoof.h"
#include "Dungeon/RoomPartWall.h"
#include "Dungeon/RoomPartPillar.h"

// Sets default values
ADungeonRoom::ADungeonRoom(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sceneRootComp = CreateDefaultSubobject<USceneComponent>("Scene Root"); 
	sceneRootComp->SetupAttachment(RootComponent);
	sceneRootComp->SetRelativeScale3D(FVector(2.0f));
}

// Called when the game starts or when spawned
void ADungeonRoom::BeginPlay(){
	Super::BeginPlay();
	
	gameInstance = GetGameInstance<UAdvancedGameInstance>();
	
}

void ADungeonRoom::Init(FIntVector _gridLoc, const FDungeonRoomParams &_params) {
	gridLoc = _gridLoc;
	params = _params;

}

void ADungeonRoom::BuildRoom(FConnectedRooms _connectedRooms){

	connectedRooms = _connectedRooms;

	if (spawningFloorBP) {
		floor = GetWorld()->SpawnActor<ASpawningFloorActor>(spawningFloorBP, GetActorLocation(), FRotator::ZeroRotator);
	} 

	if (roofBP) {
		FTransform roofTrans = FTransform(FRotator(180, 0, 0), GetActorLocation() + FVector(0, 0, 1000), GetActorScale3D());
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *roofTrans.ToString());

		roof = GetWorld()->SpawnActor<ARoomPartRoof>(roofBP, roofTrans);
		roof->SetActorScale3D(GetActorScale3D());
	}

	if (connectedRooms.front) {
		UE_LOG(LogTemp, Warning, TEXT("cennector is set"));

	}

	if (wallBP) {
		if (!connectedRooms.front) { 
			FTransform wallTrans = FTransform(FRotator(0, 180, 0), GetActorLocation() + FVector(1000, 0, 0), GetActorScale3D());
			walls.front = GetWorld()->SpawnActor<ARoomPartWall>(wallBP, wallTrans);
			walls.front->SetActorScale3D(GetActorScale3D());
		}
		if (!connectedRooms.right) {
			FTransform wallTrans = FTransform(FRotator(0, -90, 0), GetActorLocation() + FVector(0, 1000, 0), GetActorScale3D());
			walls.right = GetWorld()->SpawnActor<ARoomPartWall>(wallBP, wallTrans);
			walls.right->SetActorScale3D(GetActorScale3D());
		}
		if (!connectedRooms.back) {
			FTransform wallTrans = FTransform(FRotator(0, 0, 0), GetActorLocation() + FVector(-1000, 0, 0), GetActorScale3D());
			walls.back = GetWorld()->SpawnActor<ARoomPartWall>(wallBP, wallTrans);
			walls.back->SetActorScale3D(GetActorScale3D());
		}
		if (!connectedRooms.left) {
			FTransform wallTrans = FTransform(FRotator(0, 90, 0), GetActorLocation() + FVector(0, -1000, 0), GetActorScale3D());
			walls.left = GetWorld()->SpawnActor<ARoomPartWall>(wallBP, wallTrans);
			walls.left->SetActorScale3D(GetActorScale3D());
		}
	}

	if (pillarBP) {
		 
		float pillarDistance = 960.0f;
		 
		bool bFrontRightPillar = walls.front && walls.right || !walls.front && !walls.right && !connectedRooms.front->connectedRooms.right;
		bool bFrontLeftPillar = walls.front && walls.left || !walls.front && !walls.left && !connectedRooms.front->connectedRooms.left;
		bool bBackRightPillar = walls.back && walls.right || !walls.back && !walls.right && !connectedRooms.back->connectedRooms.right;
		bool bBackLeftPillar = walls.back && walls.left || !walls.back && !walls.left && !connectedRooms.back->connectedRooms.left;

		if (bFrontRightPillar) {
			ARoomPartPillar* pillar = GetWorld()->SpawnActor<ARoomPartPillar>(pillarBP, GetActorLocation() + FVector(pillarDistance, pillarDistance, 0), FRotator::ZeroRotator);
			pillar->SetActorScale3D(GetActorScale3D()); 
			pillars.Add(pillar);
		}
		 
		if (bFrontLeftPillar) {
			ARoomPartPillar* pillar = GetWorld()->SpawnActor<ARoomPartPillar>(pillarBP, GetActorLocation() + FVector(pillarDistance, -pillarDistance, 0), FRotator::ZeroRotator);
			pillar->SetActorScale3D(GetActorScale3D());
			pillars.Add(pillar);
		}

		if (bBackRightPillar) {
			ARoomPartPillar* pillar = GetWorld()->SpawnActor<ARoomPartPillar>(pillarBP, GetActorLocation() + FVector(-pillarDistance, pillarDistance, 0), FRotator::ZeroRotator);
			pillar->SetActorScale3D(GetActorScale3D());
			pillars.Add(pillar);
		}

		if(bBackLeftPillar){
			ARoomPartPillar* pillar = GetWorld()->SpawnActor<ARoomPartPillar>(pillarBP, GetActorLocation() + FVector(-pillarDistance, -pillarDistance, 0), FRotator::ZeroRotator);
			pillar->SetActorScale3D(GetActorScale3D());
			pillars.Add(pillar);
		}

	}
}

void ADungeonRoom::DestructRoom(){
	if (walls.front) {
		walls.front->Destroy();
	}

	if (walls.back) {
		walls.back->Destroy();
	}

	if (walls.right) {
		walls.right->Destroy();
	}

	if (walls.left) {
		walls.left->Destroy();
	}
	
	if (roof) {
		roof->Destroy();
	}

	if (floor) {
		floor->Destroy();
	}

	for (auto pillar : pillars){
		pillar->Destroy();
	}

	Destroy();
}


// Called every frame
void ADungeonRoom::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

ADungeonRoom * ADungeonRoom::Construct(AActor* owner, TSubclassOf<ADungeonRoom> classBP, FVector location, FIntVector gridLoc, const FDungeonRoomParams &params){
	
	if (!owner) return nullptr;

	UAdvancedGameInstance* gameInstance = owner->GetGameInstance<UAdvancedGameInstance>();

	if (gameInstance) {
		FTransform spawnTrans;
		spawnTrans.SetLocation(location);
		spawnTrans.SetRotation(FQuat::Identity);

		ADungeonRoom* spawnedRoom = owner->GetWorld()->SpawnActorDeferred<ADungeonRoom>(classBP, spawnTrans, owner);
		//ADungeonRoom* spawnedRoom = owner->GetWorld()->SpawnActor<ADungeonRoom>(classBP, location, FRotator::ZeroRotator);
		spawnedRoom->Init(gridLoc, params);

		UGameplayStatics::FinishSpawningActor(spawnedRoom, spawnTrans);

		ADungeon* dungeonOwner = Cast<ADungeon>(owner);
		if (dungeonOwner) {
			dungeonOwner->AddSpawnedRoom(spawnedRoom);
		}

		return spawnedRoom;
	}
	return nullptr;
}



ADungeon * ADungeonRoom::TryGetDungeon(){
	return Cast<ADungeon>(GetOwner());
}

