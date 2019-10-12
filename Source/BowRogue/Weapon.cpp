// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Projectile.h"
#include "Kismet/KismetMathLibrary.h"

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
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::Fire(const FVector &targetLoc){

	if (projectileBP) {

		if (skeletalMeshComp->DoesSocketExist("projectile")) {
			//projectileSpawnLoc = skeletalMeshComp->GetSocketLocation("projectile");
			skeletalMeshComp->GetSocketWorldLocationAndRotation("projectile", projectileSpawnLoc, projectileSpawnRot);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Socket 'projectile' not found on Weapon"));
			projectileSpawnLoc = GetActorLocation();
			projectileSpawnRot = GetActorRotation();
		}

		FRotator lookAtRot = UKismetMathLibrary::FindLookAtRotation(projectileSpawnLoc, targetLoc);

		UE_LOG(LogTemp, Warning, TEXT("Projectile spawned: %s"), *projectileSpawnLoc.ToString());
		AProjectile* spawnedProjectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, projectileSpawnLoc, lookAtRot);
	}

	

}

void AWeapon::SetFocus(const FVector & targetLoc){
	FRotator lookAtRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), targetLoc);
	SetActorRotation(lookAtRot);
}

