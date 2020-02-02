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


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arrow")
	UStaticMeshComponent * bodyMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arrow")
	UStaticMeshComponent * fletchingMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Particles")
	class UNiagaraComponent* particleTrailComp;

public:

	AArrow();
	 
	virtual void OnConstruction(const FTransform& Transform) override;


	void UpdateArrow(const FArrowUpdate &arrowUpdate);

	UStaticMeshComponent * GetMeshCompFromType(EArrowMeshType meshType);
};
