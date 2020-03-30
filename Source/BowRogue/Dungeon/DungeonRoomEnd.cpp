// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonRoomEnd.h"
#include "Actors/PortalPlatform.h"
#include "Engine/World.h"
#include "Dungeon/Dungeon.h"

void ADungeonRoomEnd::BeginPlay() {
	Super::BeginPlay();
	
	SetupPortal();

}

void ADungeonRoomEnd::SetupPortal(){
	if (!portalBP) {
		UE_LOG(LogTemp, Warning, TEXT("ADungeonRoomEnd: portalBP is empty"));
		return;
	}

	portal = GetWorld()->SpawnActor<APortalPlatform>(portalBP, GetActorLocation(), FRotator::ZeroRotator);


	//Set Portal teleport destination
	if (portal) {
		ADungeon* dungeon = TryGetDungeon();
		if (dungeon) {
			ADungeon* nextDungeon = dungeon->GetNextDungeon();

			if (nextDungeon) {
				portal->targetLocation = nextDungeon->GetSpawnLocation();
			}
		}


		portal->bUseVectorLocation = true;
	}
}
