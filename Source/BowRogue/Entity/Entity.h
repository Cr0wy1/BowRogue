// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameStructs.h"
#include "Entity.generated.h"



class AEntitySpawner;



UCLASS()
class BOWROGUE_API AEntity : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEntity();

protected:

	AEntitySpawner * spawner = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	class UHealthComponent* healthComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDeath();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeathEvent();

	UFUNCTION(BlueprintImplementableEvent, Category = "Entity")
	void OnTakeDamage(float damageAmount);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	void SetSpawner(AEntitySpawner* _spawner);


};
