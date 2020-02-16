// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalPlatform.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APortalPlatform::APortalPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	meshComp = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	RootComponent = meshComp;

	sphereComp = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	sphereComp->SetupAttachment(meshComp);
} 

// Called when the game starts or when spawned
void APortalPlatform::BeginPlay(){
	Super::BeginPlay();
	
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &APortalPlatform::OnOverlapBegin);
	sphereComp->OnComponentEndOverlap.AddDynamic(this, &APortalPlatform::OnOverlapEnd);
}

void APortalPlatform::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult){

	if (!bIsRecivingTeleport && bIsPortalActive) {
		TeleportActor(OtherActor);
	}

}

void APortalPlatform::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex){
	if (bIsRecivingTeleport) {
		bIsRecivingTeleport = false;
	}
}

void APortalPlatform::TeleportActor(AActor * actor){ 
	if (actor && targetPortal) {

		FVector portalDeltaLoc = targetPortal->GetActorLocation() - GetActorLocation();
		FVector newActorLoc = actor->GetActorLocation() + portalDeltaLoc;

		targetPortal->ReciveTeleport();
		actor->SetActorLocation(newActorLoc, true, nullptr, ETeleportType::None);
	}
}

void APortalPlatform::ReciveTeleport(){
	bIsRecivingTeleport = true;
}

// Called every frame
void APortalPlatform::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

