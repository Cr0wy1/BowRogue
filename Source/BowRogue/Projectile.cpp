// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

AProjectile::AProjectile(){

	// Use a sphere as a simple collision representation
	collisionMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision Mesh"));
	collisionMeshComp->BodyInstance.SetCollisionProfileName("Projectile");
	collisionMeshComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
																		
	collisionMeshComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	collisionMeshComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = collisionMeshComp;

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

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor) {
		UE_LOG(LogTemp, Warning, TEXT("Hittet Actor: %s"), *OtherActor->GetName());
	}
	
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics()){

		FDamageEvent damageEvent;
		OtherActor->TakeDamage(10.0f, damageEvent, nullptr, nullptr);
		

		OtherComp->AddImpulseAtLocation(GetVelocity() * hitImpulse, GetActorLocation());
		SetActorLocation(GetActorLocation() + (GetActorForwardVector() * 20));
		AttachToActor(OtherActor, FAttachmentTransformRules::KeepWorldTransform);


		//Destroy();
	} 
}


void AProjectile::SetDummy() {
	collisionMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	projectileMovement->SetAutoActivate(false);

}
