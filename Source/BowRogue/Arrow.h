// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Arrow.generated.h"

/**
 * 
 */
UCLASS()
class BOWROGUE_API AArrow : public AProjectile
{
	GENERATED_BODY()
	
protected:



	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arrow")
	UStaticMeshComponent * headMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arrow")
	UStaticMeshComponent * bodyMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arrow")
	UStaticMeshComponent * fletchingMeshComp;

public:

	AArrow();

	

};
