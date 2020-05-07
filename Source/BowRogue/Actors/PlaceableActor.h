// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaceableActor.generated.h"



class UMaterialInterface;
class UMeshComponent;



UCLASS()
class BOWROGUE_API APlaceableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaceableActor();

protected:

	TMap<UMeshComponent*, UMaterialInterface*> defaultMaterialMap;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitDefaultMaterialMap();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetMaterialToAllMeshes(UMaterialInterface* material);

	UFUNCTION(BlueprintCallable)
	void SetMaterialDefaultToAllMeshes();

	UFUNCTION(BlueprintCallable, Category = "Placement")
	void SetPreview(bool isPreview = true);

	UFUNCTION(BlueprintCallable)
	TArray<UMeshComponent*> GetMeshComponents();
};
