// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonDoor.h"
#include "Components/StaticMeshComponent.h"
#include "BowRogueCharacter.h"

// Sets default values
ADungeonDoor::ADungeonDoor(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshFrame = CreateDefaultSubobject<UStaticMeshComponent>("Frame");
	RootComponent = meshFrame;

	meshGate = CreateDefaultSubobject<UStaticMeshComponent>("Gate");
	meshGate->SetupAttachment(meshFrame);
}

// Called when the game starts or when spawned
void ADungeonDoor::BeginPlay(){
	Super::BeginPlay();
	
}


// Called every frame
void ADungeonDoor::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void ADungeonDoor::OpenDoor(){
	bIsOpen = true;
	OnOpenDoor();
}

void ADungeonDoor::CloseDoor(){
	bIsOpen = false;
	OnCloseDoor();
}



