// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonRoom.h"
#include "DungeonGenerator.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "StructureAsset.h"
#include "AdvancedGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "SpawningFloorActor.h"
#include "Dungeon.h"

// Sets default values
ADungeonRoom::ADungeonRoom(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sceneRootComp = CreateDefaultSubobject<USceneComponent>("Scene Root"); 
	sceneRootComp->SetupAttachment(RootComponent);
	sceneRootComp->SetRelativeScale3D(FVector(2.0f));

	meshRoofComp = CreateDefaultSubobject<UStaticMeshComponent>("Roof Mesh");
	meshRoofComp->SetRelativeLocationAndRotation(FVector(0, 0, 500), FRotator(180, 0, 0));
	meshRoofComp->SetupAttachment(sceneRootComp);

	meshWall1Comp = CreateDefaultSubobject<UStaticMeshComponent>("Wall1 Mesh");
	meshWall1Comp->SetRelativeLocationAndRotation(FVector(500, 0, 0), FRotator(0, -180, 0));
	meshWall1Comp->SetupAttachment(sceneRootComp);

	meshWall2Comp = CreateDefaultSubobject<UStaticMeshComponent>("Wall2 Mesh");
	meshWall2Comp->SetRelativeLocationAndRotation(FVector(0, 500, 0), FRotator(0, -90, 0));
	meshWall2Comp->SetupAttachment(sceneRootComp);

	meshWall3Comp = CreateDefaultSubobject<UStaticMeshComponent>("Wall3 Mesh");
	meshWall3Comp->SetRelativeLocationAndRotation(FVector(-500, 0, 0), FRotator(0, 0, 0));
	meshWall3Comp->SetupAttachment(sceneRootComp);

	meshWall4Comp = CreateDefaultSubobject<UStaticMeshComponent>("Wall4 Mesh");
	meshWall4Comp->SetRelativeLocationAndRotation(FVector(0, -500, 0), FRotator(0, 90, 0));
	meshWall4Comp->SetupAttachment(sceneRootComp);


}

// Called when the game starts or when spawned
void ADungeonRoom::BeginPlay(){
	Super::BeginPlay();
	
	gameInstance = GetGameInstance<UAdvancedGameInstance>();

	if (!meshWall) {
		UE_LOG(LogTemp, Warning, TEXT("ADungeonRoom: meshWall is nullptr"));
	}
	
	BuildRoom();
}

void ADungeonRoom::BuildRoom(){
	if (spawningFloorBP) {
		GetWorld()->SpawnActor<ASpawningFloorActor>(spawningFloorBP, GetActorLocation(), FRotator::ZeroRotator);
	}

	UStructureAsset* structureAsset = gameInstance->GetStructureAsset();
	if (structureAsset && structureAsset->bossPortal_BP) {
		if (params.roomtype == ERoomType::END) {
			GetWorld()->SpawnActor<AActor>(structureAsset->bossPortal_BP, GetActorLocation(), FRotator::ZeroRotator);
		}
	}
}


void ADungeonRoom::Init(FIntVector _gridLoc, const FDungeonRoomParams &_params){
	gridLoc = _gridLoc; 
	params = _params;
	  
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

void ADungeonRoom::AddConnector(const FGridDir & dir){
	UE_LOG(LogTemp, Warning, TEXT("Connector checked"));

	switch (dir.GetType()) {
	case EGridDir::FRONT:
		meshWall1Comp->SetStaticMesh(nullptr);
		//meshWall1Comp->SetStaticMesh(meshDoorWall); 
		break;
	case EGridDir::RIGHT:
		meshWall2Comp->SetStaticMesh(nullptr); 
		break;
	case EGridDir::BACK:
		meshWall3Comp->SetStaticMesh(nullptr);
		break;
	case EGridDir::LEFT:
		meshWall4Comp->SetStaticMesh(nullptr);
		break;
	}

}



void ADungeonRoom::AdjustRoomConnections(){
	if (dungeonGenerator) {
		
	}
}

ADungeon * ADungeonRoom::TryGetDungeon(){
	return Cast<ADungeon>(GetOwner());
}

