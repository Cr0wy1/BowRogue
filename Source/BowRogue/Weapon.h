// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"



class AProjectile;



UENUM()
enum class EShootingType : uint8 {
	SINGLE,
	SALVE,
	RAPID,
	CHARGE
};

USTRUCT(BlueprintType)
struct BOWROGUE_API FWeaponProperties {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EShootingType shootingType = EShootingType::SINGLE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float shotDelay = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 magazineSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 maxShotAmount = 100;
};


UCLASS()
class BOWROGUE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:

	

	float lastShotTime = 0.0f;

	float startShootingTime = 0.0f;
	float stopShootingTime = 0.0f;
	float cShootingDuration = 0.0f;

	bool bIsShooting = false;
	const struct FCrosshairResult* crossResult = nullptr;

	FVector projectileSpawnLoc;
	FRotator projectileSpawnRot;

	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* skeletalMeshComp;

	//PROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AProjectile> projectileBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FWeaponProperties properties;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Blueprint Events
	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void OnStartShooting();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void OnStopShooting();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	virtual void Fire(const FVector targetLoc);

	virtual void StartShooting(const struct FCrosshairResult* _crossResult);
	virtual void StopShooting();

	void SetFocus(const FVector &targetLoc);

	FORCEINLINE float GetCurrentShootingDuration() const { return cShootingDuration; }
};
