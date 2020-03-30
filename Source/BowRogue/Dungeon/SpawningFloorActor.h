// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawningFloorActor.generated.h"



class AGeometryPawn;



UENUM(BlueprintType)
enum class EGeoType : uint8 {
	CUBE,
	SPHERE,
	PYRAMID,
};



USTRUCT(BlueprintType)
struct BOWROGUE_API FSpawnGeoParam{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGeoType geoType = EGeoType::CUBE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float radius = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(MakeEditWidget))
	FVector location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AGeometryPawn>> spawnList;
};



UCLASS()
class BOWROGUE_API ASpawningFloorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawningFloorActor();


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSpawnGeoParam> spawnGeoParams;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnCreatures();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DrawDebugSpawnPoints();
};
