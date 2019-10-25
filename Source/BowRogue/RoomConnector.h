// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomConnector.generated.h"



class ADungeonRoom;



UCLASS()
class BOWROGUE_API ARoomConnector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomConnector();

protected:

	ADungeonRoom * roomA = nullptr;
	ADungeonRoom * roomB = nullptr;

	//UPROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UStaticMesh* doorA = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UStaticMesh* doorB = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UStaticMesh* floor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UStaticMesh* wall = nullptr;

	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger")
	class UBoxComponent* triggerBoxComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "mesh")
	UStaticMeshComponent* meshDoorA;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "mesh")
	UStaticMeshComponent* meshDoorB;

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static ARoomConnector* Construct(TSubclassOf<ARoomConnector> tempalteBP, ADungeonRoom * roomA, ADungeonRoom * roomB);
};
