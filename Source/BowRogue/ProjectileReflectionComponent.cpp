// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileReflectionComponent.h"
#include "Projectiles/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UProjectileReflectionComponent::UProjectileReflectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts 
void UProjectileReflectionComponent::BeginPlay(){
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UProjectileReflectionComponent::OnOverlapBegin);
	
}

void UProjectileReflectionComponent::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult){
	
	AProjectile* projectile = Cast<AProjectile>(OtherActor); 
	if (projectile) {   

		if (catchedProjectiles.Num() < 1) {
			firstCatchTime = GetWorld()->GetTimeSeconds();
		}

		catchedProjectiles.Add(projectile);

		projectile->GetProjectileMovement()->ProjectileGravityScale = 0.0f;
	}
}
 

// Called every frame
void UProjectileReflectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (auto projectile : catchedProjectiles){
		if (projectile && projectile->GetOwner() != GetOwner()) {
			if (projectile->GetProjectileMovement()->Velocity.Size() > 0.1) {
				projectile->GetProjectileMovement()->Velocity *= velocityShrink;
			}
			else {
				projectile->GetProjectileMovement()->StopMovementImmediately();
			}
		}
		else {
			catchedProjectiles.Remove(projectile);
		}
	}

	if (catchedProjectiles.Num() > 0 && GetWorld()->GetTimeSeconds() > firstCatchTime + throwTimeAfterCatch) {
		for (auto projectile : catchedProjectiles) {

			FVector deltaLoc = projectile->GetOwner()->GetActorLocation() - projectile->GetActorLocation();
			deltaLoc.Normalize();

			projectile->GetProjectileMovement()->Velocity = deltaLoc * throwSpeed;
			projectile->GetProjectileMovement()->ProjectileGravityScale = 1.0f;

			projectile->SetOwner(GetOwner());

			projectile->GetCollisionMeshComp()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
		}

		catchedProjectiles.Reset();
	}
}

