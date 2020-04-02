// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h" //ApplyDamage
#include "GameFramework/DamageType.h"

AProjectile::AProjectile(){

	//sceneRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	//SetRootComponent(sceneRootComp);

	// Use a sphere as a simple collision representation
	collisionMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision Mesh"));
	collisionMeshComp->BodyInstance.SetCollisionProfileName("Projectile");
	collisionMeshComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
																		
	collisionMeshComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	collisionMeshComp->CanCharacterStepUpOn = ECB_No;
	//collisionMeshComp->SetupAttachment(sceneRootComp);
	SetRootComponent(collisionMeshComp);
	

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
		projectileMovement->InitialSpeed = speed;
		projectileMovement->ProjectileGravityScale = weight;
	}
}


void AProjectile::BeginPlay(){
	Super::BeginPlay();



	projectileMovement->OnProjectileBounce.AddDynamic(this, &AProjectile::OnBounce);

	spawnScale = GetActorScale3D();

	if (bDrawDebug) {
		FVector startLoc = GetActorLocation();
		FVector endLoc = startLoc + (GetActorForwardVector() * 100.0f);
		DrawDebugPoint(GetWorld(), startLoc, 10.0f, FColor::Green, true, 20);
		DrawDebugDirectionalArrow(GetWorld(), startLoc, endLoc, 100.0f, FColor::Blue, true, 20.0f, 0, 1.0f);
	}

	effectManager.CallAllOnSpawn();
}

// Called every frame
void AProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!bInitIsDummy && lastTickLocation != GetActorLocation()) {

		distanceTraveled += FVector::Distance(GetActorLocation(), lastTickLocation);

		lastTickLocation = GetActorLocation();
	}

	effectManager.CallAllOnTick(DeltaTime);
}

void AProjectile::UpdateProjectile(const FProjectileUpdate & projectileUpdate){
	for (auto effect : projectileUpdate.addEffects) {
		AddProjectileEffect(effect);
	}

	for (auto attribute : projectileUpdate.attributeUpdates) {
		UpdateAttribute(attribute);
	}
}

void AProjectile::UpdateAttribute(const FProjectileAttributeUpdate & projectileAttribute){
	switch (projectileAttribute.type){
	case EProjectileAttributeType::DAMAGE :
		impactDamage += projectileAttribute.value;
		break;
	case EProjectileAttributeType::KNOCKBACK:
		hitImpulse += projectileAttribute.value;
		break;
	case EProjectileAttributeType::SPEED:
		speed += projectileAttribute.value;
		break;
	case EProjectileAttributeType::WEIGHT:
		weight += projectileAttribute.value;
		break;
	default:
		break;
	}
}



void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){

	if (OtherActor && OtherActor != this) {
		UE_LOG(LogTemp, Warning, TEXT("Hittet Actor: %s"), *OtherActor->GetName());



		FDamageEvent damageEvent;
		UGameplayStatics::ApplyDamage(OtherActor, impactDamage, nullptr, this, UDamageType::StaticClass());
	
		//OtherActor->TakeDamage(impactDamage, damageEvent, nullptr, nullptr);

		// Only add impulse and destroy projectile if we hit a physics
		if (OtherComp && OtherComp->IsSimulatingPhysics()) {
			OtherComp->AddImpulseAtLocation(GetVelocity() * hitImpulse, GetActorLocation());

			//Destroy();
		}

		SetActorLocation(GetActorLocation() + (GetActorForwardVector() * 20));
		AttachToActor(OtherActor, FAttachmentTransformRules::KeepWorldTransform);

		OnImpact(Hit);

		effectManager.CallAllOnHit(Hit);

	}

	//draw debug impact point
	if (bDrawDebug) {
		DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 5, FColor::Red, true, 20);
	}
}

void AProjectile::OnBounce(const FHitResult & ImpactResult, const FVector & ImpactVelocity){
	++bounceCounter;
}



void AProjectile::SetDummy() {
	collisionMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	projectileMovement->SetAutoActivate(false);

} 


UProjectileEffectBase * AProjectile::AddProjectileEffect(TSubclassOf<UProjectileEffectBase> newEffect){
	FName newEffectName = newEffect.GetDefaultObject()->GetNameId();
	if (effectManager.HasEffect(newEffectName)) {
		UE_LOG(LogTemp, Warning, TEXT("effect allready exists"));
		return nullptr;
	}

	UProjectileEffectBase* addedEffect = NewObject<UProjectileEffectBase>(this, newEffect);
	addedEffect->Init(this);
	effectManager.effects.Add(addedEffect);

	return addedEffect;
}


//Projectile Effects
void AProjectile::SplitProjectile(TSubclassOf<AProjectile> projectile_BP){ 
	FTransform trans;
	trans.SetLocation( GetActorLocation() );
	trans.SetRotation( GetActorRightVector().ToOrientationQuat() );
	trans.SetScale3D(GetActorScale3D() * 0.5f);
	 
	GetWorld()->SpawnActor<AProjectile>(projectile_BP, trans);

	trans.SetRotation((GetActorRightVector() * -1.0f).ToOrientationQuat());  
	GetWorld()->SpawnActor<AProjectile>(projectile_BP, trans);
}

void AProjectile::UpdateScaleByTraceDistance(float scalor){
	FVector newScale = spawnScale + (distanceTraveled * scalor);
	SetActorScale3D(newScale);
}

