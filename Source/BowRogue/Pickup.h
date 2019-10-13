// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"



class USphereComponent;



UCLASS()
class BOWROGUE_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:

	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	USphereComponent * sphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	UStaticMeshComponent * meshComp;

	//PROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	bool bAdjustMeshToSphere = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float bAdjustBorderSpace = 6.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void AdjustMeshToSphere(float borderSpace = 1.0f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	virtual void Take();
};
