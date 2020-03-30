// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomPartBase.h"
#include "DungeonRoom.h"

// Sets default values
ARoomPartBase::ARoomPartBase(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoomPartBase::BeginPlay(){
	Super::BeginPlay();
	
}

// Called every frame
void ARoomPartBase::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void ARoomPartBase::Init(ADungeonRoom * _dungeonRoom){
	dungeonRoom = _dungeonRoom;
}

