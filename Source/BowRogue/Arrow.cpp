// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AArrow::AArrow() {

	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Body Mesh");
	bodyMeshComp->SetupAttachment(collisionMeshComp, "body");

	fletchingMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Fletching Mesh");
	fletchingMeshComp->SetupAttachment(bodyMeshComp, "fletching");

	projectileMovement->bShouldBounce = false;
	hitImpulse = 100.0f;
}
 

