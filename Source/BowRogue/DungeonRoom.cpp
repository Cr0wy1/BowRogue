// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonRoom.h"
#include "Entity.h"
#include "DungeonGenerator.h"
#include "Engine/World.h"
#include "EntitySpawner.h"
#include "RoomConnector.h"
#include "Kismet/GameplayStatics.h"
#include "StructureAsset.h"
#include "Pickup.h"
#include "AdvancedGameInstance.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADungeonRoom::ADungeonRoom(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshFloorComp = CreateDefaultSubobject<UStaticMeshComponent>("Floor Mesh");
	meshFloorComp->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(0, 0, 0));
	meshFloorComp->SetRelativeScale3D(FVector(2.0f));
	meshFloorComp->SetupAttachment(RootComponent);

	meshRoofComp = CreateDefaultSubobject<UStaticMeshComponent>("Roof Mesh");
	meshRoofComp->SetRelativeLocationAndRotation(FVector(0, 0, 500), FRotator(180, 0, 0));
	meshRoofComp->SetupAttachment(meshFloorComp);

	meshWall1Comp = CreateDefaultSubobject<UStaticMeshComponent>("Wall1 Mesh");
	meshWall1Comp->SetRelativeLocationAndRotation(FVector(500, 0, 0), FRotator(0, -180, 0));
	meshWall1Comp->SetupAttachment(meshFloorComp);

	meshWall2Comp = CreateDefaultSubobject<UStaticMeshComponent>("Wall2 Mesh");
	meshWall2Comp->SetRelativeLocationAndRotation(FVector(0, 500, 0), FRotator(0, -90, 0));
	meshWall2Comp->SetupAttachment(meshFloorComp);

	meshWall3Comp = CreateDefaultSubobject<UStaticMeshComponent>("Wall3 Mesh");
	meshWall3Comp->SetRelativeLocationAndRotation(FVector(-500, 0, 0), FRotator(0, 0, 0));
	meshWall3Comp->SetupAttachment(meshFloorComp);

	meshWall4Comp = CreateDefaultSubobject<UStaticMeshComponent>("Wall4 Mesh");
	meshWall4Comp->SetRelativeLocationAndRotation(FVector(0, -500, 0), FRotator(0, 90, 0));
	meshWall4Comp->SetupAttachment(meshFloorComp);
}

// Called when the game starts or when spawned
void ADungeonRoom::BeginPlay(){
	Super::BeginPlay();
	
	if (!meshDoorWall) {
		UE_LOG(LogTemp, Warning, TEXT("ADungeonRoom: meshDoorWall is nullptr"));
	}

	if (!meshWall) {
		UE_LOG(LogTemp, Warning, TEXT("ADungeonRoom: meshWall is nullptr"));
	}
}

void ADungeonRoom::OnAllEntitiesKilled(){
	bIsClear = true;
	bIsOpen = true;
	OnRoomClear.Broadcast();
	//UE_LOG(LogTemp, Warning, TEXT("Room cleared!"));

}

void ADungeonRoom::Init(ADungeonGenerator * _dungeonGenerator, FIntVector _gridLoc, const FDungeonRoomParams &_params){
	
	dungeonGenerator = _dungeonGenerator;
	gridLoc = _gridLoc;
	params = _params;

	if (!params.bSpawnEntities) {

		bIsClear = true;
		bIsOpen = true;
	}

	FItemData* itemData = FItemData::FromId(dungeonGenerator->GetAdvGameInstance()->GetItemDataTable(), "0");
	APickup::Construct(this, GetActorLocation() + FVector(0, 0, 300), itemData);
	
}

// Called every frame
void ADungeonRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ADungeonRoom * ADungeonRoom::Construct(ADungeonGenerator * dungeonGenerator, TSubclassOf<ADungeonRoom> classBP, FVector location, FIntVector gridLoc, const FDungeonRoomParams &params){
	
	if (dungeonGenerator) {
		FTransform spawnTrans;
		spawnTrans.SetLocation(location);
		spawnTrans.SetRotation(FQuat::Identity);

		UStructureAsset* structureAsset = dungeonGenerator->GetStructureAsset();
		if (structureAsset && structureAsset->bossPortal_BP) {
			if (params.roomtype == ERoomType::BOSS) {
				dungeonGenerator->GetWorld()->SpawnActor<AActor>(structureAsset->bossPortal_BP, location, FRotator::ZeroRotator);
			}
		}

		ADungeonRoom* spawnedRoom = dungeonGenerator->GetWorld()->SpawnActorDeferred<ADungeonRoom>(classBP, spawnTrans, dungeonGenerator);
		//ADungeonRoom* spawnedRoom = dungeonGenerator->GetWorld()->SpawnActor<ADungeonRoom>(classBP, location, FRotator::ZeroRotator);
		spawnedRoom->Init(dungeonGenerator, gridLoc, params);

		UGameplayStatics::FinishSpawningActor(spawnedRoom, spawnTrans);


		return spawnedRoom;
	}
	return nullptr;
}

void ADungeonRoom::AddConnector(const FGridDir & dir, ARoomConnector * connector){
	connectors.Add(dir, connector);

	if (meshDoorWall) {
		UE_LOG(LogTemp, Warning, TEXT("added connector"));

		switch (dir.GetType()) {
		case EGridDir::FRONT:
			meshWall1Comp->SetStaticMesh(meshDoorWall);
			break;
		case EGridDir::RIGHT:
			meshWall2Comp->SetStaticMesh(meshDoorWall);
			break;
		case EGridDir::BACK:
			meshWall3Comp->SetStaticMesh(meshDoorWall);
			break;
		case EGridDir::LEFT:
			meshWall4Comp->SetStaticMesh(meshDoorWall);
			break;
		}
	}

}

void ADungeonRoom::PrepareEnter(){
	spawner = AEntitySpawner::Construct(this, GetActorLocation());
	if (spawner) {
		spawner->OnAllEntitiesRemoved.AddDynamic(this, &ADungeonRoom::OnAllEntitiesKilled);
		spawner->SpawnEntities(spawnPattern);
	}
}

void ADungeonRoom::SetOpen(bool isOpen){
	bIsOpen = isOpen;
}

