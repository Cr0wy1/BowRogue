// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Bow.generated.h"



class AArrow;
/**
 * 
 */
UCLASS()
class BOWROGUE_API ABow : public AWeapon
{
	GENERATED_BODY()


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bow")
	bool bIsDrawing = false;


	AArrow * drawArrow = nullptr;

	//COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	UChildActorComponent* drawArrowActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	class UAnimationAsset* drawMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	class UAnimationAsset* releaseMontage;

	virtual void BeginPlay() override;

	virtual void StartShooting(const struct FCrosshairResult* _crossResult) override;
	virtual void StopShooting() override;



public:

	ABow();
};
