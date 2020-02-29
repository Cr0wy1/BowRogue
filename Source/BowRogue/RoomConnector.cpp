// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomConnector.h"
#include "DungeonRoom.h"
#include "DungeonDoor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARoomConnector::ARoomConnector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshFloor = CreateDefaultSubobject<UStaticMeshComponent>("Floor Mesh");
	RootComponent = meshFloor;

	triggerBoxComp = CreateDefaultSubobject<UBoxComponent>("Trigger");
	triggerBoxComp->SetupAttachment(meshFloor);

	doorAActorComp = CreateDefaultSubobject<UChildActorComponent>("DoorA Actor");
	doorAActorComp->SetRelativeLocationAndRotation(FVector(-150, 0, 0), FRotator::ZeroRotator);
	doorAActorComp->SetupAttachment(meshFloor);
	
	doorBActorComp = CreateDefaultSubobject<UChildActorComponent>("DoorB Actor");
	doorBActorComp->SetRelativeLocationAndRotation(FVector(150, 0, 0), FRotator::ZeroRotator);
	doorBActorComp->SetupAttachment(meshFloor);

	meshWallA = CreateDefaultSubobject<UStaticMeshComponent>("WallA Mesh");
	meshWallA->SetRelativeLocationAndRotation(FVector(0, 100, 0), FRotator(0, -90, 0));
	meshWallA->SetupAttachment(meshFloor);

	meshWallB = CreateDefaultSubobject<UStaticMeshComponent>("WallB Mesh");
	meshWallB->SetRelativeLocationAndRotation(FVector(0, -100, 0), FRotator(0, 90, 0));
	meshWallB->SetupAttachment(meshFloor);

	meshRoof = CreateDefaultSubobject<UStaticMeshComponent>("Roof Mesh");
	meshRoof->SetRelativeLocationAndRotation(FVector(0, -0, 200), FRotator::ZeroRotator);
	meshRoof->SetupAttachment(meshFloor);
}

// Called when the game starts or when spawned
void ARoomConnector::BeginPlay()
{
	Super::BeginPlay();
	
	triggerBoxComp->OnComponentBeginOverlap.AddDynamic(this, &ARoomConnector::OnTriggerOverlapBegin);

	doorA = Cast<ADungeonDoor>(doorAActorComp->GetChildActor());
	doorB = Cast<ADungeonDoor>(doorBActorComp->GetChildActor());

	//UE_LOG(LogTemp, Warning, TEXT("Connector %s BeginPlay"), *GetName());

}

void ARoomConnector::Init(ADungeonRoom * _roomA, ADungeonRoom * _roomB){
	roomA = _roomA;
	roomB = _roomB;

}

void ARoomConnector::OnTriggerOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult){
	
	if (!bIsTriggerActive) return;

	//UE_LOG(LogTemp, Warning, TEXT("Overlap!"));

	if (doorA->IsOpen() && !doorB->IsOpen()) {
		doorA->CloseDoor();
		//roomB->PrepareEnter();
		doorB->OpenDoor();
	}
	else if(!doorA->IsOpen() && doorB->IsOpen()){
		doorB->CloseDoor();
		//roomA->PrepareEnter();
		doorA->OpenDoor();
	}

	bIsTriggerActive = false;
}


// Called every frame
void ARoomConnector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ARoomConnector * ARoomConnector::Construct(TSubclassOf<ARoomConnector> tempalteBP, ADungeonRoom * roomA, ADungeonRoom * roomB){


	ARoomConnector* spawnedConnector = nullptr;
	//UE_LOG(LogTemp, Warning, TEXT("spawn roomConnector"));
	if (roomA && roomB) {
		
		FRotator spawnRot = FRotator::ZeroRotator;
		
		FIntVector dir = roomB->GetGridLoc() - roomA->GetGridLoc();
		if (dir.X == 0) {
			spawnRot.Yaw = 90.0f * dir.Y;
		}
		else {
			if (dir.X < 0) {
				spawnRot.Yaw = 180.0f;
			}
		}

		FVector spawnPos = (roomA->GetActorLocation() + roomB->GetActorLocation()) / 2.0f;
		spawnedConnector = roomA->GetWorld()->SpawnActor<ARoomConnector>(tempalteBP, spawnPos, spawnRot);
		spawnedConnector->Init(roomA, roomB);

		//UE_LOG(LogTemp, Warning, TEXT("Connector %s after BeginPlay"), *spawnedConnector->GetName());
		//roomA->OnRoomClear.AddDynamic(spawnedConnector, &ARoomConnector::OnRoomAClear);
		//roomB->OnRoomClear.AddDynamic(spawnedConnector, &ARoomConnector::OnRoomBClear);
	}

	return spawnedConnector;
}

