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

	drawArrowActor->AttachToComponent(skeletalMeshComp, FAttachmentTransformRules::KeepRelativeTransform, "projectile");
}

void ABow::StartShooting(const FCrosshairResult * _crossResult){
	Super::StartShooting(_crossResult);
	
	bIsDrawing = true;

	if (drawMontage) {
		//skeletalMeshComp->PlayAnimation(drawMontage, false);
	}
}

void ABow::StopShooting(){

	bIsDrawing = false;

	if (releaseMontage) {
		//skeletalMeshComp->SetPlayRate(3.0f);
		//skeletalMeshComp->PlayAnimation(releaseMontage, false);
	}

	Super::StopShooting();
}
