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

 

