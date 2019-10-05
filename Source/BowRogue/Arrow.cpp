// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

AArrow::AArrow() {

	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Body Mesh");
	bodyMeshComp->SetupAttachment(collisionComp);

	headMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Head Mesh");
	headMeshComp->SetupAttachment(bodyMeshComp, "head");

	fletchingMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Fletching Mesh");
	fletchingMeshComp->SetupAttachment(bodyMeshComp, "fletching");
	
}