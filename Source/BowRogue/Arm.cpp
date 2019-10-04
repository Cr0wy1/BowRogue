// Fill out your copyright notice in the Description page of Project Settings.


#include "Arm.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimationAsset.h"

// Sets default values
AArm::AArm() {
	PrimaryActorTick.bCanEverTick = false;

	armMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Arm Mesh");
	SetRootComponent(armMeshComp);
	armMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	handSkeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>("Hand Skeletal");
	handSkeletalComp->SetupAttachment(armMeshComp, FName("hand"));
	handSkeletalComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AArm::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AArm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArm::SetHandRotation(float value) {
	handSkeletalComp->SetRelativeRotation(FRotator(0.0f, value, 0.0f));
}

void AArm::SetHandFlat() {
	if (flatHandAnimation) {
		handSkeletalComp->PlayAnimation(flatHandAnimation, true);
	}
	SetHandRotation(-90.0f);
}

void AArm::SetHandFist() {
	if (fistHandAnimation) {
		handSkeletalComp->PlayAnimation(fistHandAnimation, true);
	}
	SetHandRotation(0.0f);
}

