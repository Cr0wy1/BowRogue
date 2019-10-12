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

	AArrow * drawArrow = nullptr;

	//COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	UChildActorComponent* drawArrowActor;

	virtual void BeginPlay() override;

public:

	ABow();
};
