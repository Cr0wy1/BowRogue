// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Containers/Queue.h"
#include "EntitySpawnerComponent.generated.h"



class AEntity;



UENUM()
enum class ESpawnArrayOrder : uint8 {
	TOP_BOTTOM,
	BOTTOM_TOP,
	RANDOM,
	RANDOM_UNIQUE,
};



USTRUCT()
struct BOWROGUE_API FEntitySpawn {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEntity> entityBP;

	UPROPERTY(EditAnywhere)
	float delayToNextEntity = 1.0f;
};



USTRUCT()
struct BOWROGUE_API FEntitySpawnParams {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ESpawnArrayOrder spawnArrayOrder = ESpawnArrayOrder::TOP_BOTTOM;

	UPROPERTY(EditAnywhere)
	TArray<FEntitySpawn> entitySpawns;

	UPROPERTY(EditAnywhere)
	int32 repeats = 1;

	UPROPERTY(EditAnywhere)
	float timeToNextParams = 1.0f;
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWROGUE_API UEntitySpawnerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEntitySpawnerComponent();

protected:

	TQueue<FEntitySpawn> spawnQueue;

	float nextSpawnTime = 0.0f;

	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TArray<FEntitySpawnParams> spawnParamsArray;

public:	

	UFUNCTION(BlueprintCallable)
	void StartSpawning();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
