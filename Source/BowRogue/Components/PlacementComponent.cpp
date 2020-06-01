// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacementComponent.h"
#include "Player/AdvancedCharacter.h"
#include "Actors/PlaceableActor.h"
#include "Components/CrosshairTraceComponent.h"
#include "Engine/World.h"
#include "Materials/MaterialInstance.h"

// Sets default values for this component's properties
UPlacementComponent::UPlacementComponent(){	
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPlacementComponent::BeginPlay(){
	Super::BeginPlay();

	AAdvancedCharacter* advCharacter = Cast<AAdvancedCharacter>(GetOwner());
	
	if (advCharacter) {
		crosshairResult = advCharacter->GetCrosshairTraceComp()->GetCrosshairResultPtr();
	}

	
}


// Called every frame
void UPlacementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsPlacementActive) {
		if (currentPreviewActor) {
			UpdatePreviewActor();
		}
		else {
			SpawnPreviewActor();
		}
	}
	else if (currentPreviewActor) {
		DestroyPreviewActor();
	}
}


void UPlacementComponent::SpawnPreviewActor(){
	if (placeableActorBP && crosshairResult) {
		if (crosshairResult->IsActorHit()) {
			FHitResult hitResult = crosshairResult->hitResult;
			currentPreviewActor = GetWorld()->SpawnActor<APlaceableActor>(placeableActorBP, hitResult.ImpactPoint, FRotator::ZeroRotator);
			if (currentPreviewActor) {
				currentPreviewActor->SetMaterialToAllMeshes(cannotPlaceMaterial);
				currentPreviewActor->SetPreview();
			}
		}
	}
}

void UPlacementComponent::UpdatePreviewActor(){
	if (currentPreviewActor && crosshairResult) {
		currentPreviewActor->SetActorLocation(crosshairResult->hitResult.Location);
		
		if (currentPreviewActor->CanBePlaced()) {
			currentPreviewActor->SetMaterialDefaultToAllMeshes();
		} 
		else {
			currentPreviewActor->SetMaterialToAllMeshes(cannotPlaceMaterial);
		}
		currentPreviewActor->OnPreviewUpdate();
	}
}

void UPlacementComponent::DestroyPreviewActor(){
	if (currentPreviewActor) {
		currentPreviewActor->Destroy();
		currentPreviewActor = nullptr;
	}
}

void UPlacementComponent::PlaceActor(){
	if (currentPreviewActor) {
		currentPreviewActor->SetPreview(false);
		currentPreviewActor->SetMaterialDefaultToAllMeshes();
		currentPreviewActor->OnPlace();
		currentPreviewActor = nullptr;
	}
}




void UPlacementComponent::SetPlaceableActorBP(TSubclassOf<APlaceableActor> _placeableActor){

}

