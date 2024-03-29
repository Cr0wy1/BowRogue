// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"
#include "Entity/EntityController.h"
#include "Entity/EntitySpawner.h"
#include "Engine/World.h"
#include "Components/HealthComponent.h"

// Sets default values
AEntity::AEntity(){
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	healthComponent = CreateDefaultSubobject<UHealthComponent>("Health");
	healthComponent->OnDeath.AddDynamic(this, &AEntity::OnDeath);

	AIControllerClass = AEntityController::StaticClass();
}

// Called when the game starts or when spawned
void AEntity::BeginPlay(){
	Super::BeginPlay();
	
}

void AEntity::OnDeath(){
	//UE_LOG(LogTemp, Warning, TEXT("i am Death"));

	OnDeathEvent();

	if (spawner) {
		spawner->RemovedSpawnedEntity(this);
	}

	Destroy();
}

// Called every frame
void AEntity::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

float AEntity::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser){

	//UE_LOG(LogTemp, Warning, TEXT("you Damage me!"));

	OnTakeDamage(DamageAmount);

	healthComponent->ApplyDamage(DamageAmount);

	return DamageAmount;
}

void AEntity::SetSpawner(AEntitySpawner * _spawner){
	spawner = _spawner;
	if (spawner) {
		spawner->AddSpawnedEntity(this);
	}
}



