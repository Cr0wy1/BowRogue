// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

AProjectile::AProjectile(){

	sceneRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(sceneRootComp);

	// Use a sphere as a simple collision representation
	collisionMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision Mesh"));
	collisionMeshComp->BodyInstance.SetCollisionProfileName("Projectile");
	collisionMeshComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
																		
	collisionMeshComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	collisionMeshComp->CanCharacterStepUpOn = ECB_No;
	collisionMeshComp->SetupAttachment(sceneRootComp);
	

	// Use a ProjectileMovementComponent to govern this projectile's movement
	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	projectileMovement->UpdatedComponent = collisionMeshComp;
	projectileMovement->InitialSpeed = 3000.f;
	projectileMovement->MaxSpeed = 3000.f;
	projectileMovement->bRotationFollowsVelocity = true;
	projectileMovement->bShouldBounce = true;
	
}

void AProjectile::OnConstruction(const FTransform & Transform){
	if (bInitIsDummy) {
		InitialLifeSpan = 0.0f;

		SetDummy();
	}
	else {
		// Die after 3 seconds by default
		InitialLifeSpan = 20.0f;
	}
}

void AProjectile::BeginPlay(){
	Super::BeginPlay();

	if (bDrawDebug) {
		FVector startLoc = GetActorLocation();
		FVector endLoc = startLoc + (GetActorForwardVector() * 100.0f);
		DrawDebugPoint(GetWorld(), startLoc, 10.0f, FColor::Green, true, 20);
		DrawDebugDirectionalArrow(GetWorld(), startLoc, endLoc, 100.0f, FColor::Blue, true, 20.0f, 0, 1.0f);
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){

	if (OtherActor && OtherActor != this) {
		UE_LOG(LogTemp, Warning, TEXT("Hittet Actor: %s"), *OtherActor->GetName());

		FDamageEvent damageEvent;
		OtherActor->TakeDamage(10.0f, damageEvent, nullptr, nullptr);

		// Only add impulse and destroy projectile if we hit a physics
		if (OtherComp && OtherComp->IsSimulatingPhysics()) {

			OtherComp->AddImpulseAtLocation(GetVelocity() * hitImpulse, GetActorLocation());
			SetActorLocation(GetActorLocation() + (GetActorForwardVector() * 20));
			AttachToActor(OtherActor, FAttachmentTransformRules::KeepWorldTransform);

			//Destroy();
		}
	}

	//draw debug impact point
	if (bDrawDebug) {
		DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 5, FColor::Blue, true, 20);
	}
}




void AProjectile::SetDummy() {
	collisionMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	projectileMovement->SetAutoActivate(false);

}
