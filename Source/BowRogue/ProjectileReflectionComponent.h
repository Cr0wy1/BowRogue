// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "ProjectileReflectionComponent.generated.h"



class AProjectile;




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWROGUE_API UProjectileReflectionComponent : public USphereComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectileReflectionComponent();

protected:

	float firstCatchTime = 0.0f;

	TArray<AProjectile*> catchedProjectiles;

	UPROPERTY(EditAnywhere)
	float throwSpeed = 1000.0f;

	UPROPERTY(EditAnywhere)
	float velocityShrink = 0.9f;

	UPROPERTY(EditAnywhere)
	float throwTimeAfterCatch = 5.0f;

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
