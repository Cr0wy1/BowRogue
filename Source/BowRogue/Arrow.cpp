// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Niagara\Public\NiagaraComponent.h"

AArrow::AArrow() {

	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Body Mesh");
	bodyMeshComp->SetupAttachment(collisionMeshComp, "body");
	bodyMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	fletchingMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Fletching Mesh");
	fletchingMeshComp->SetupAttachment(bodyMeshComp, "fletching");
	fletchingMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	projectileMovement->bShouldBounce = false;
	hitImpulse = 100.0f;
	 
	particleTrailComp = CreateDefaultSubobject<UNiagaraComponent>("ParticleTrail");
	particleTrailComp->SetupAttachment(fletchingMeshComp);
}

void AArrow::OnConstruction(const FTransform & Transform){
	Super::OnConstruction(Transform);
	if (bInitIsDummy) {
		particleTrailComp->bAutoActivate = false;
		particleTrailComp->Deactivate();
	}
}

void AArrow::UpdateArrow(const FArrowUpdate & arrowUpdate){
	UE_LOG(LogTemp, Warning, TEXT("ArrowUpdate!")); 

	for (auto meshUpdate : arrowUpdate.meshUpdates){

		UStaticMeshComponent* targetMesh = GetMeshCompFromType(meshUpdate.meshType);

		if (targetMesh) {
			if (meshUpdate.newMesh) {
				targetMesh->SetStaticMesh(meshUpdate.newMesh);
			}
			if (meshUpdate.bOverrideColor) {
				//TODO set update color function
			}
		} 

	}
}

UStaticMeshComponent * AArrow::GetMeshCompFromType(EArrowMeshType meshType){
	UStaticMeshComponent* targetMesh = nullptr;

	switch (meshType) {
	case EArrowMeshType::HEAD:
		targetMesh = collisionMeshComp;
		break;
	case EArrowMeshType::BODY:
		targetMesh = bodyMeshComp;
		break;
	case EArrowMeshType::FLETCHING:
		targetMesh = fletchingMeshComp;
		break;
	default:
		break;
	}

	return targetMesh;
}

 

