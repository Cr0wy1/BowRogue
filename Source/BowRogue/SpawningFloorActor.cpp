// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningFloorActor.h"
#include "DrawDebugHelpers.h"
#include "GeometryPawn.h"
#include "Engine/World.h"

// Sets default values
ASpawningFloorActor::ASpawningFloorActor(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DrawDebugSpawnPoints();
	
}

// Called when the game starts or when spawned
void ASpawningFloorActor::BeginPlay(){
	Super::BeginPlay();
	
	SpawnCreatures();
}

void ASpawningFloorActor::SpawnCreatures(){
	for (auto spawnParam : spawnGeoParams) {
		if (spawnParam.spawnList.Num() > 0) {
			int32 randIndex = FMath::Rand() % spawnParam.spawnList.Num();

			GetWorld()->SpawnActor<AGeometryPawn>(spawnParam.spawnList[randIndex], GetActorLocation() + spawnParam.location, FRotator::ZeroRotator);
		}
	}
}

// Called every frame
void ASpawningFloorActor::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}


void ASpawningFloorActor::DrawDebugSpawnPoints(){
	FlushPersistentDebugLines(GetWorld());
	FVector center;
	for (auto spawnGeoParam : spawnGeoParams) {

		center = GetActorLocation() + spawnGeoParam.location;
		center.Z += spawnGeoParam.radius;

		switch (spawnGeoParam.geoType) {
		case EGeoType::CUBE:
			DrawDebugBox(GetWorld(), center, FVector(spawnGeoParam.radius), FColor::Red, true, 100, 0, 4.0f);
			break;
		case EGeoType::SPHERE:
			DrawDebugSphere(GetWorld(), center, spawnGeoParam.radius, 16, FColor::Red, true, 100, 0, 4.0f);
			break;
		case EGeoType::PYRAMID:

			break;
		default:
			break;
		}
	}
}

