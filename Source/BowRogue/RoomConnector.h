// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomConnector.generated.h"



class ADungeonRoom;
class ADungeonDoor;



UCLASS()
class BOWROGUE_API ARoomConnector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomConnector();

	ADungeonRoom * roomA = nullptr;
	ADungeonRoom * roomB = nullptr;

	ADungeonDoor * doorA = nullptr;
	ADungeonDoor * doorB = nullptr;

protected:

	bool bIsTriggerActive = true;

	//UPROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UStaticMesh* doorAMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UStaticMesh* doorBMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UStaticMesh* floorMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UStaticMesh* wallMesh = nullptr;

	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger")
	class UBoxComponent* triggerBoxComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "mesh")
	UChildActorComponent* doorAActorComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "mesh")
	UChildActorComponent* doorBActorComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "mesh")
	UStaticMeshComponent* meshFloor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "mesh")
	UStaticMeshComponent* meshWallA;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "mesh")
	UStaticMeshComponent* meshWallB;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "mesh")
	UStaticMeshComponent* meshRoof;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Init(ADungeonRoom * _roomA, ADungeonRoom * _roomB);

	UFUNCTION()
	void OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnRoomAClear();

	UFUNCTION()
	void OnRoomBClear();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static ARoomConnector* Construct(TSubclassOf<ARoomConnector> tempalteBP, ADungeonRoom * roomA, ADungeonRoom * roomB);
};
