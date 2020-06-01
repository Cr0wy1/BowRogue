// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "PlaneTraceComponent.generated.h"





UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWROGUE_API UPlaneTraceComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlaneTraceComponent();

protected:

	UPROPERTY(EditAnywhere)
	bool bDrawDebug = false;

	// Called when the game starts
	virtual void BeginPlay() override;

	FHitResult TraceLine(const FVector& location);

public:	
	
	//Returns true if checkedDifference is smaller then maxDifference
	UFUNCTION(BlueprintCallable, Category = "PlaneTrace")
	bool TraceCheck(float &checkedDifference, float maxDifference = 100.0f);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void DrawLines(const FVector &location);
};
