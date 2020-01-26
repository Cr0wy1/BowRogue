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

	float arrowBaseSpeed;

	UPROPERTY(EditAnywhere)
	float drawAnimTime = 0.36f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bow")
	bool bIsDrawing = false;


	AArrow * drawArrow = nullptr;

	//COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	UChildActorComponent* drawArrowActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	class UAnimMontage* drawMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	class UAnimMontage* releaseMontage;

	virtual void BeginPlay() override;

	virtual void BeforeProjectileFired(AProjectile* templateProjectile) override;
	virtual void AfterProjectileFired(AProjectile* firedProjectile) override;

	virtual void StartShooting(const struct FCrosshairResult* _crossResult) override;
	virtual void StopShooting() override;



public:

	ABow();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetDrawPercent() const { return FMath::Clamp(cShootingDuration / (drawAnimTime / properties.chargeSpeed), 0.0f, 1.0f); }
};
