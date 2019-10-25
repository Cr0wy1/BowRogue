// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameStructs.h"
#include "Entity.generated.h"



class AEntitySpawner;



UCLASS()
class BOWROGUE_API AEntity : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEntity();

protected:

	AEntitySpawner * spawner = nullptr;

	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	class UAttributeComponent* attributeComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDeath();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	void SetSpawner(AEntitySpawner* _spawner);

	//spawn the entity and return it, return nullptr if spawner is nullptr
	static AEntity* Spawn(TSubclassOf<AEntity> templateClass, const FVector &Location, AEntitySpawner* spawner);

	//spawn the entity and return it, return nullptr if spawner is nullptr
	static AEntity* Spawn(const FEntitySpawnParams &params, AEntitySpawner* spawner);
};
