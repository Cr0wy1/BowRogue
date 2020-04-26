// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/Entity.h"
#include "GeometryPawn.generated.h"

UCLASS()
class BOWROGUE_API AGeometryPawn : public AEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGeometryPawn();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector targetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = "Force")
	FVector constantForce;

	UPROPERTY(EditAnywhere, Category = "Force")
	FVector constantVelocity;

	UPROPERTY(EditAnywhere, Category = "Attribute")
	float health = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Attribute")
	float damage = 10.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddRotateImpulse(float amount);

	UFUNCTION(BlueprintCallable)
	void RotateForward(float amount);

	UFUNCTION(BlueprintCallable)
	void JumpAtDirection(FVector direction, float impulseAmount, float heightAmount = 1.0f);

	UFUNCTION(BlueprintCallable)
	void JumpToTargetLocation(float impulseAmount, float heightAmount = 1.0f);
};
