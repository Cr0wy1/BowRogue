// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/PlaceableActor.h"
#include "Tower.generated.h"



class USphereComponent;
class UStaticMeshComponent;
class AEntity;
class UPlaneTraceComponent;



UENUM()
enum class ETowerTargetPrio : uint8 {
	RANDOM,
	NEAREST,
	STRONGEST,
	LAST
};


UCLASS()
class BOWROGUE_API ATower : public APlaceableActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATower();

protected:

	AEntity * currentTarget;
	TArray<AEntity*> overlappedEntities;

	float lastFireTime = 0.0f;

	UPROPERTY(EditAnywhere)
	bool shouldFire = true;

	UPROPERTY(EditAnywhere)
	float fireDelay = 1.0f;

	UPROPERTY(EditAnywhere)
	bool shouldRotate = true;

	UPROPERTY(EditAnywhere)
	float rotationSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	float groundCheckRadius = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* meshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* sphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* placeShapeMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPlaneTraceComponent* planeTraceComp;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnSetPreview() override;

	void Fire();

	UFUNCTION(BlueprintImplementableEvent, Category = "Tower")
	void OnFire();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "Tower")
	FORCEINLINE AEntity * GetCurrentTarget() const { return currentTarget; }

	UFUNCTION(BlueprintCallable, Category = "Tower")
	FORCEINLINE TArray<AEntity*> GetAllInRange() const { return overlappedEntities; }

public:	
	 
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnPlace() override;

	virtual bool CanBePlaced() override;

	UFUNCTION(BlueprintCallable, Category = "Tower")
	AEntity* GetNearestEntitiy() const;

	UFUNCTION(BlueprintCallable, Category = "Tower")
	bool GetLookAtEntityRotation(FRotator &lookAtRotation, FVector relativeStartLocation = FVector(0,0,0)) const;

	UFUNCTION(BlueprintCallable, Category = "Tower")
	bool GetUpdateRotationAmount(FRotator &updateRotation, float deltaTime, FRotator currentRotation, FVector relativeStartLocation = FVector(0, 0, 0)) const;

	UFUNCTION(BlueprintCallable, Category = "Tower")
	FORCEINLINE bool HasTarget() const { return currentTarget; }
};
