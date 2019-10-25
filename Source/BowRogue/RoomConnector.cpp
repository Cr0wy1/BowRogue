// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomConnector.h"
#include "DungeonRoom.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARoomConnector::ARoomConnector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	triggerBoxComp = CreateDefaultSubobject<UBoxComponent>("Trigger");
	//triggerBoxComp->OnComponentBeginOverlap.AddDynamic(this, )

	meshFloor = CreateDefaultSubobject<UStaticMeshComponent>("Floor Mesh");
	RootComponent = meshFloor;

	meshDoorA = CreateDefaultSubobject<UStaticMeshComponent>("DoorA Mesh");
	meshDoorA->SetRelativeLocationAndRotation(FVector(100, 0, 0), FRotator());
	meshDoorA->SetupAttachment(meshFloor);

	meshDoorB = CreateDefaultSubobject<UStaticMeshComponent>("DoorB Mesh");
	meshDoorB->SetRelativeLocationAndRotation(FVector(-100, 0, 0), FRotator());
	meshDoorB->SetupAttachment(meshFloor);

	meshWallA = CreateDefaultSubobject<UStaticMeshComponent>("WallA Mesh");
	meshWallA->SetRelativeLocationAndRotation(FVector(0, 100, 0), FRotator(0, -90, 0));
	meshWallA->SetupAttachment(meshFloor);

	meshWallB = CreateDefaultSubobject<UStaticMeshComponent>("WallB Mesh");
	meshWallB->SetRelativeLocationAndRotation(FVector(0, -100, 0), FRotator(0, 90, 0));
	meshWallB->SetupAttachment(meshFloor);

	meshRoof = CreateDefaultSubobject<UStaticMeshComponent>("Roof Mesh");
	meshRoof->SetRelativeLocationAndRotation(FVector(0, -0, 200), FRotator());
	meshRoof->SetupAttachment(meshFloor);
}

// Called when the game starts or when spawned
void ARoomConnector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomConnector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ARoomConnector * ARoomConnector::Construct(TSubclassOf<ARoomConnector> tempalteBP, ADungeonRoom * roomA, ADungeonRoom * roomB){

	if (roomA && roomB) {
		//FVector spawnPos = roomA->GetActorLocation() 
	}

	//roomA->GetWorld()->SpawnActor<ARoomConnector>(tempalteBP, );

	return nullptr;
}

