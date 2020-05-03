// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceableActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/MeshComponent.h"

// Sets default values
APlaceableActor::APlaceableActor(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	  
}

// Called when the game starts or when spawned
void APlaceableActor::BeginPlay(){
	Super::BeginPlay();
	
}

void APlaceableActor::InitDefaultMaterialMap(){
	defaultMaterialMap.Reset();
	for (auto meshComp : GetMeshComponents()) {
		if (meshComp) {
			defaultMaterialMap.Add(meshComp, meshComp->GetMaterial(0));
		}
	}
}

void APlaceableActor::SetMaterialDefaultToAllMeshes(){
	for (auto it = defaultMaterialMap.CreateIterator(); it; ++it) {
		if (it->Key && it->Value) {
			it->Key->SetMaterial(0, it->Value);
		}
	}
}

// Called every frame
void APlaceableActor::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void APlaceableActor::SetMaterialToAllMeshes(UMaterialInterface * material){
	if (material) {

		if (defaultMaterialMap.Num() < 1) {
			InitDefaultMaterialMap();
		}

		for (auto meshComp : GetMeshComponents()) {
			if (meshComp) {
				meshComp->SetMaterial(0, material);
			}
		}
	}
}

void APlaceableActor::SetPreview(){
	SetActorEnableCollision(false);
}

TArray<UMeshComponent*> APlaceableActor::GetMeshComponents(){
	TArray<UMeshComponent*> result;
	TArray<UActorComponent*> actorComps = GetComponentsByClass(UMeshComponent::StaticClass());
	for (auto comp : actorComps) {

		UMeshComponent* meshComp = Cast<UMeshComponent>(comp);
		if (meshComp) {
			result.Add(meshComp);
		}
	}
	
	return result;
}

