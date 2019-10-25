// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"
#include "EntityController.h"
#include "AttributeComponent.h"
#include "EntitySpawner.h"
#include "Engine/World.h"

// Sets default values
AEntity::AEntity(){
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	attributeComp = CreateDefaultSubobject<UAttributeComponent>("Attributs");
	attributeComp->OnDeath.AddDynamic(this, &AEntity::OnDeath);

	AIControllerClass = AEntityController::StaticClass();
}

// Called when the game starts or when spawned
void AEntity::BeginPlay(){
	Super::BeginPlay();
	
}

void AEntity::OnDeath(){
	UE_LOG(LogTemp, Warning, TEXT("i am Death"));

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

	UE_LOG(LogTemp, Warning, TEXT("you Damage me!"));

	attributeComp->ApplyDamage(DamageAmount);

	return DamageAmount;
}

void AEntity::SetSpawner(AEntitySpawner * _spawner){
	spawner = _spawner;
	if (spawner) {
		spawner->AddSpawnedEntity(this);
	}
}

AEntity * AEntity::Spawn(TSubclassOf<AEntity> templateClass, const FVector & Location, AEntitySpawner * spawner){
	return Spawn(FEntitySpawnParams(templateClass, Location), spawner);
}

AEntity * AEntity::Spawn(const FEntitySpawnParams & params, AEntitySpawner * spawner){
	if (spawner) {
		AEntity* spawnedEntity = spawner->GetWorld()->SpawnActor<AEntity>(params.templateClass, params.location, params.rotation);
		if (spawnedEntity) {
			spawnedEntity->SetSpawner(spawner);
		}
		
	
		return spawnedEntity;
	}
	
	return nullptr;
}

