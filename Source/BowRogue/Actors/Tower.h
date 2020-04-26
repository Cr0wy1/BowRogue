// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"



class USphereComponent;
class UStaticMeshComponent;
class AEntity;



UENUM()
enum class ETowerTargetPrio : uint8 {
	RANDOM,
	NEAREST,
	STRONGEST,
	LAST
};


UCLASS()
class BOWROGUE_API ATower : public AActor{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATower();

protected:

	AEntity * currentTarget;
	TArray<AEntity*> overlappedEntities;


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* meshComp;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* sphereComp;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

};
