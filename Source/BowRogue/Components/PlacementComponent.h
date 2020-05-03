// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlacementComponent.generated.h"



class APlaceableActor;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWROGUE_API UPlacementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlacementComponent();

protected:

	const struct FCrosshairResult* crosshairResult;

	APlaceableActor * currentPreviewActor = nullptr;

	UPROPERTY(EditAnywhere, Category = "Placement")
	bool bIsPlacementActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	class UMaterialInterface* cannotPlaceMaterial;

	UPROPERTY(EditAnywhere, Category = "Placement")
	TSubclassOf<APlaceableActor> placeableActorBP;

	// Called when the game starts
	virtual void BeginPlay() override;

	void SpawnPreviewActor();
	void UpdatePreviewActor();
	void DestroyPreviewActor();

	UFUNCTION(BlueprintCallable, Category = "Placement")
	void PlaceActor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Placement")
	void SetPlaceableActorBP(TSubclassOf<APlaceableActor> _placeableActor);

	UFUNCTION(BlueprintCallable, Category = "Placement")
	void SetPlacementActive(bool placementActive = true) { bIsPlacementActive = placementActive; }
};
