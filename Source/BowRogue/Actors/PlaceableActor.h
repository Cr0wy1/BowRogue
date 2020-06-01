// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStructs.h"
#include "PlaceableActor.generated.h"



class UMaterialInterface;
class UMeshComponent;
class UStaticMeshComponent;



UCLASS()
class BOWROGUE_API APlaceableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaceableActor();

protected:

	UPROPERTY(EditAnywhere, Category = "PlaceableData")
	FDataTableRowHandle placeableRowHandle;

	TMap<UMeshComponent*, UMaterialInterface*> defaultMaterialMap;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitDefaultMaterialMap();

	virtual void OnSetPreview();

	UFUNCTION(BlueprintImplementableEvent, Category = "PlaceableActor")
	void OnPlaceEvent();

	UFUNCTION(BlueprintImplementableEvent, Category = "PlaceableActor")
	void OnPreviewUpdateEvent();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnPlace();

	virtual void OnPreviewUpdate();

	virtual bool CanBePlaced();


	UFUNCTION(BlueprintCallable)
	void SetMaterialToAllMeshes(UMaterialInterface* material);

	UFUNCTION(BlueprintCallable)
	void SetMaterialDefaultToAllMeshes();

	UFUNCTION(BlueprintCallable, Category = "Placement")
	void SetPreview(bool isPreview = true);

	UFUNCTION(BlueprintCallable)
	TArray<UMeshComponent*> GetMeshComponents();

	UFUNCTION(BlueprintCallable)
	TArray<UStaticMeshComponent*> GetStaticMeshComponents();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool HasPlaceableData() const { return placeableRowHandle.DataTable; }

	UFUNCTION(BlueprintCallable)
	FPlaceableData GetPlaceableData() const;
	//static APlaceableActor* Construct(TSubclassOf<APlaceableActor> classBP, FVector location, FRotator rotation = FRotator::ZeroRotator);
};
