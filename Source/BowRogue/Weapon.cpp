// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Projectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "CrosshairTraceComponent.h"

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

		AProjectile* spawnedProjectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, projectileSpawnLoc, lookAtRot, projectileSpawnParams);
		
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
		if (properties.shootingType == EShootingType::CHARGE && crossResult) {
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

