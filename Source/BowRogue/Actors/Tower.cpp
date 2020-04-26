// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Entity/Entity.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATower::ATower(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	RootComponent = meshComp;

	sphereComp = CreateDefaultSubobject<USphereComponent>("Detection Sphere");
	sphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	sphereComp->SetupAttachment(meshComp);
	
}

// Called when the game starts or when spawned
void ATower::BeginPlay(){
	Super::BeginPlay();
	
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnOverlapBegin);
	sphereComp->OnComponentEndOverlap.AddDynamic(this, &ATower::OnOverlapEnd);
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
	

	//
}

