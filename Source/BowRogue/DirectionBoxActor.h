// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DirectionBoxActor.generated.h"



class UBoxComponent;
class UArrowComponent;



UCLASS()
class BOWROGUE_API ADirectionBoxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADirectionBoxActor();

protected:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* sceneComp;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* arrowComp;

	UPROPERTY(EditAnywhere)
	float boxSize = 250.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "DirectionObject")
	FORCEINLINE FVector GetDirection() const;
};
