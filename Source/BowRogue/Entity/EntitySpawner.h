// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStructs.h"
#include "EntitySpawner.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllEntitiesRemoved);


class AEntity;



UCLASS()
class BOWROGUE_API AEntitySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEntitySpawner();

protected:

	TArray<AEntity*> spawnedEntities;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	FOnAllEntitiesRemoved OnAllEntitiesRemoved;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void AddSpawnedEntity(AEntity* spawnedEntity);
	void RemovedSpawnedEntity(AEntity* spawnedEntity);

	//return spawned AEntitySpawner, return nullptr if owner is nullptr
	static AEntitySpawner* Construct(AActor* owner, const FVector &Location);

	FORCEINLINE int32 GetSpawnedNum() const { return spawnedEntities.Num(); }
};
