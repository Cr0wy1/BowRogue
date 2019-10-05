// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AProjectile::AProjectile(){

	// Use a sphere as a simple collision representation
	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	collisionComp->InitSphereRadius(5.0f);
	collisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	collisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		// set up a notification for when this component hits something blocking

																						// Players can't walk on it
	collisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	collisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = collisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	projectileMovement->UpdatedComponent = collisionComp;
	projectileMovement->InitialSpeed = 3000.f;
	projectileMovement->MaxSpeed = 3000.f;
	projectileMovement->bRotationFollowsVelocity = true;
	projectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 20.0f;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		//Destroy();
	}
}
