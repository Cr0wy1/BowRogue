// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Projectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "CrosshairTraceComponent.h"
#include "Item.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h" //for finsihActorSpawning

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	skeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetRootComponent(skeletalMeshComp);

	
	
} 

// Called when the game starts or when spawned
void AWeapon::BeginPlay(){
	Super::BeginPlay();
	
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if (bIsShooting && crossResult) {
		cShootingDuration = GetWorld()->GetTimeSeconds() - startShootingTime;

		if (properties.shootingType != EShootingType::CHARGE) {
			Fire(crossResult->hitResult.ImpactPoint);
		}
		
		//TODO Maybe refactor this block
		if (properties.shootingType == EShootingType::SINGLE) {
			StopShooting();
		}
	}
}

void AWeapon::Fire(const FVector targetLoc){

	

	//check shot delay time
	if (GetWorld()->GetTimeSeconds() < (lastShotTime + properties.shotDelay)) return;

	if (projectileBP) {

		if (skeletalMeshComp->DoesSocketExist("projectile")) {
			skeletalMeshComp->GetSocketWorldLocationAndRotation("projectile", projectileSpawnLoc, projectileSpawnRot);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Socket 'projectile' not found on Weapon"));
			projectileSpawnLoc = GetActorLocation();
			projectileSpawnRot = GetActorRotation();
		}

		FRotator lookAtRot = UKismetMathLibrary::FindLookAtRotation(projectileSpawnLoc, targetLoc);

		//UE_LOG(LogTemp, Warning, TEXT("Projectile spawned: %s"), *projectileSpawnLoc.ToString());

		FActorSpawnParameters projectileSpawnParams;
		projectileSpawnParams.Owner = this;

		FTransform trans;
		trans.SetLocation(projectileSpawnLoc);
		trans.SetRotation(FQuat(lookAtRot));
		AProjectile* spawnedProjectile = GetWorld()->SpawnActorDeferred<AProjectile>(projectileBP, trans);
		OnProjectileSpawned(spawnedProjectile);
		UGameplayStatics::FinishSpawningActor(spawnedProjectile, trans);
		//AProjectile* spawnedProjectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, projectileSpawnLoc, lookAtRot, projectileSpawnParams);
		
		
		//Set shot time
		lastShotTime = GetWorld()->GetTimeSeconds();
	}

}

void AWeapon::StartShooting(const struct FCrosshairResult* _crossResult){
	crossResult = _crossResult;
	startShootingTime = GetWorld()->GetTimeSeconds();
	bIsShooting = true;

	OnStartShooting();
}

void AWeapon::StopShooting(){
	if (bIsShooting) {
		if (crossResult && properties.shootingType == EShootingType::CHARGE &&  properties.minShootingTime < cShootingDuration) {
			Fire(crossResult->hitResult.ImpactPoint);
		}
		//UE_LOG(LogTemp, Warning, TEXT("ShootingDuration: %f"), cShootingDuration);

		cShootingDuration = 0.0f;
		stopShootingTime = GetWorld()->GetTimeSeconds();
		bIsShooting = false;

		OnStopShooting();
	}
}


void AWeapon::SetFocus(const FVector & targetLoc){
	FRotator lookAtRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), targetLoc);
	SetActorRotation(lookAtRot);
}


void AWeapon::AttachItem(FItemData * itemData) {
	if (!itemData) {
		UE_LOG(LogTemp, Warning, TEXT("AWeapon::AttachItem: itemdata is nullptr"));
		return;
	}

	if (itemData->itemBP) {

	}
	else if (itemData->mesh) {
		//UE_LOG(LogTemp, Warning, TEXT("mesh: %s"), itemData->mesh->Get);

		if (skeletalMeshComp->DoesSocketExist("slot_01")) {
			
			//UStaticMeshComponent* newMesh = FObjectInitializer::CreateDefaultSubobject<UStaticMeshComponent>(this, *itemData->name.ToString());
			UStaticMeshComponent* newMesh = NewObject<UStaticMeshComponent>(this, "test");
			newMesh->RegisterComponent();

			if (newMesh) {
				newMesh->SetStaticMesh(itemData->mesh);
				//newMesh->SetupAttachment(skeletalMeshComp, "slot_01");
				newMesh->AttachToComponent(skeletalMeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "slot_01");
			}

		}

	}
}

