// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonDoor.generated.h"

UCLASS()
class BOWROGUE_API ADungeonDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonDoor();

protected:

	bool bIsOpen = false;

	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Door")
	class UStaticMeshComponent* meshFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Door")
	class UStaticMeshComponent* meshGate;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void OnOpenDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void OnCloseDoor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OpenDoor();

	UFUNCTION()
	void CloseDoor();

	FORCEINLINE bool IsOpen()const { return bIsOpen; }

};
