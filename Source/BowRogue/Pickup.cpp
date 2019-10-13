// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Detection Sphere"));
	RootComponent = sphereComp;
	sphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	meshComp->SetupAttachment(sphereComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	if(bAdjustMeshToSphere) {
		AdjustMeshToSphere(bAdjustBorderSpace);
	}
	
}


// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::Take()
{
}

void APickup::AdjustMeshToSphere(float borderSpace) {
	FVector boundMin, boundMax;
	meshComp->GetLocalBounds(boundMin, boundMax);
	FVector deltaBound = boundMin + boundMax;

	float maxAxeLength = (boundMin.GetAbs() + boundMax.GetAbs()).GetMax();
	float sphereDia = (sphereComp->GetScaledSphereRadius() - borderSpace) * 2.0f;
	float scalorFactor = sphereDia / maxAxeLength;

	//Center Mesh by bounding box origin
	meshComp->SetRelativeLocation(-(deltaBound*scalorFactor*0.5f));

	//scale mesh to sphere border
	meshComp->SetWorldScale3D(FVector(scalorFactor));
	

	//UE_LOG(LogTemp, Warning, TEXT("Pickup Bounds: Min:%s, Max:%s"), *boundMin.ToCompactString(), *boundMax.ToCompactString());
	//UE_LOG(LogTemp, Warning, TEXT("Pickup maxAxeLength:%f sphereRadius:%f"), maxAxeLength, sphereDia);
}

