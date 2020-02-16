// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalPlatform.generated.h"

UCLASS()
class BOWROGUE_API APortalPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalPlatform();

protected:

	UPROPERTY(EditAnywhere)
	bool bIsPortalActive = true;

	bool bIsRecivingTeleport = false;


	UPROPERTY(EditAnywhere)
	APortalPlatform* targetPortal = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Portal")
	class UStaticMeshComponent * meshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Portal")
	class USphereComponent* sphereComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void TeleportActor(AActor* actor);

public:	

	void SetTargetPortal(APortalPlatform* _targetPortal) { targetPortal = _targetPortal; }
	void SetPortalActive(bool isActive) { bIsPortalActive = isActive; }

	void ReciveTeleport();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
