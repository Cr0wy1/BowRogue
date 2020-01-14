// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GeometryPawn.generated.h"

UCLASS()
class BOWROGUE_API AGeometryPawn : public APawn
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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintCallable)
	void AddRotateImpulse(float amount);

	UFUNCTION(BlueprintCallable)
	void JumpAtDirection(FVector direction, float impulseAmount, float heightAmount = 1.0f);

	UFUNCTION(BlueprintCallable)
	void JumpToTargetLocation(float impulseAmount, float heightAmount = 1.0f);
};
