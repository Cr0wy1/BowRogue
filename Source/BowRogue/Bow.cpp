// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow.h"
#include "Arrow.h"
#include "Components/SkeletalMeshComponent.h"

ABow::ABow() {

	drawArrowActor = CreateDefaultSubobject<UChildActorComponent>("Draw Arrow");
	drawArrowActor->SetupAttachment(skeletalMeshComp, "projectile");
	//drawArrowActor->SetChildActorClass(AArrow::StaticClass());

	drawArrow = Cast<AArrow>(drawArrowActor->GetChildActor());
	if (drawArrow) {
		drawArrow->bInitIsDummy = true;
		drawArrow->InitialLifeSpan = 0.0f;
	}
}


void ABow::BeginPlay(){
	Super::BeginPlay();

	drawArrowActor->AttachToComponent(skeletalMeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "projectile");
}
