// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"
#include "Entity/Entity.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/PlaneTraceComponent.h"

// Sets default values
ATower::ATower(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	RootComponent = meshComp;

	sphereComp = CreateDefaultSubobject<USphereComponent>("Detection Sphere");
	sphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	sphereComp->SetupAttachment(meshComp);

	placeShapeMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Place Shape Collision Mesh");
	sphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	placeShapeMeshComp->SetupAttachment(meshComp);

	planeTraceComp = CreateDefaultSubobject<UPlaneTraceComponent>("PlaneTraceComp");
	planeTraceComp->SetupAttachment(RootComponent);
}



// Called when the game starts or when spawned
void ATower::BeginPlay(){
	Super::BeginPlay();
	
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnOverlapBegin);
	sphereComp->OnComponentEndOverlap.AddDynamic(this, &ATower::OnOverlapEnd);
}

void ATower::OnSetPreview(){
	placeShapeMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ATower::Fire(){
	OnFire();
}

void ATower::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult){
	

	AEntity* entity = Cast<AEntity>(OtherActor);
	if (entity) {
		UE_LOG(LogTemp, Warning, TEXT("ATower: Begin Overlap!"));
		overlappedEntities.Add(entity);
	}
}
 
void ATower::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex){

	AEntity* entity = Cast<AEntity>(OtherActor);
	if (entity) {
		UE_LOG(LogTemp, Warning, TEXT("ATower: End Overlap!"));
		overlappedEntities.Remove(entity);
		if (currentTarget == entity) {
			currentTarget = nullptr;
		}
	}

}



// Called every frame
void ATower::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if (overlappedEntities.Num() > 0 && !currentTarget) {
		int32 iRand = FMath::RandRange(0, overlappedEntities.Num() - 1);
		AEntity* entity = overlappedEntities[iRand];

		if (entity) { 
			currentTarget = entity;
			FRotator lookAtRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), entity->GetActorLocation());
		}
		
	}
	

	if (shouldRotate) {
		FRotator lookAtRotation;
		if (GetLookAtEntityRotation(lookAtRotation)) {
			float deltaZRot = lookAtRotation.Yaw - GetActorRotation().Yaw;
			float addZRot = deltaZRot * DeltaTime * rotationSpeed;
			AddActorLocalRotation(FRotator(0, addZRot, 0));
		}
	}

	if(shouldFire && HasTarget()){
		if (GetWorld()->GetTimeSeconds() > lastFireTime + fireDelay) {
			Fire();
			lastFireTime = GetWorld()->GetTimeSeconds();
		}
	}

}

void ATower::OnPlace(){
	Super::OnPlace();

	//float checkedDiffrence;
	//planeTraceComp->TraceCheck(checkedDiffrence);
}

bool ATower::CanBePlaced(){
	
	if (Super::CanBePlaced()) {
		if (planeTraceComp) {
			float checkedDifference;
			if (planeTraceComp->TraceCheck(checkedDifference, 200)) {

				TArray<AActor*> overlappedActors;
				placeShapeMeshComp->GetOverlappingActors(overlappedActors);

				if (overlappedActors.Num() < 1) {

					return true;
				}
			}
		}
	}
	
	return false;
}

AEntity * ATower::GetNearestEntitiy() const{
	AEntity* nearestEntitiy = nullptr;
	float nearestLength = 10000000.0f;

	for (AEntity* entitiy : overlappedEntities) {
		float length = (entitiy->GetActorLocation() - GetActorLocation()).Size();
		if (length < nearestLength) {
			nearestLength = length;
			nearestEntitiy = entitiy;
		}
	}

	return nearestEntitiy;
}

bool ATower::GetLookAtEntityRotation(FRotator &lookAtRotation, FVector relativeStartLocation) const{

	if (currentTarget) {
		lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation() + relativeStartLocation, currentTarget->GetActorLocation());
		return true;
	}

	return false;
}

bool ATower::GetUpdateRotationAmount(FRotator & updateRotation, float deltaTime, FRotator currentRotation, FVector relativeStartLocation) const{
	FRotator lookAtRotation;
	if (GetLookAtEntityRotation(lookAtRotation, relativeStartLocation)) {
		FRotator deltaRot = lookAtRotation - currentRotation;
		updateRotation = deltaRot * deltaTime * rotationSpeed;
		
		return true;
	}

	return false;
}

