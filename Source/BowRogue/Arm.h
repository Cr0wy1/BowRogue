// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arm.generated.h"



class UStaticMeshComponent;
class USkeletalMeshComponent;
class UAnimationAsset;



UCLASS()
class BOWROGUE_API AArm : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* armMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		USkeletalMeshComponent* handSkeletalComp;

	//PROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimationAsset* fistHandAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimationAsset* flatHandAnimation;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetHandRotation(float value);

	void SetHandFlat();
	void SetHandFist();

};

