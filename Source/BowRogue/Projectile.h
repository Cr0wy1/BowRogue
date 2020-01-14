// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectBase.h"
#include "Projectile.generated.h"



UCLASS(Blueprintable, BlueprintType)
class BOWROGUE_API UProjectileEffectClass : public UObject{
	GENERATED_BODY()
		
protected:
	UPROPERTY(EditDefaultsOnly)
	FName nameId = "NONE";

	UPROPERTY(BlueprintReadOnly)
	class AProjectile * mainProjectile;
public:
		UProjectileEffectClass() {}

		virtual void BeginDestroy() override {
			UE_LOG(LogTemp, Warning, TEXT("I am getting destroyed!"));
			Super::BeginDestroy();
		}

	virtual void Init(class AProjectile * _mainProjectile);

	virtual void Tick(float deltaTime) {
		OnTickEvent(deltaTime);
	}

	virtual void OnHit(const FHitResult& hitResult) {
		OnHitEvent(hitResult);
	}

	virtual void OnSpawn() {
		OnSpawnEvent();
	}

	UFUNCTION(BlueprintImplementableEvent)
	void OnHitEvent(const FHitResult& hitResult);

	UFUNCTION(BlueprintImplementableEvent)
	void OnTickEvent(float deltaTime);

	UFUNCTION(BlueprintImplementableEvent)
	void OnSpawnEvent();


	FORCEINLINE FName GetNameId() const { return nameId; }
};





UCLASS()
class BOWROGUE_API AProjectile : public AActor
{
	GENERATED_BODY()


protected:

	FProjectileEffectManager effectManager;

	UPROPERTY()
	TArray<UProjectileEffectClass*> effects;

	UPROPERTY(BlueprintReadOnly)
	int32 bounceCounter;

	UPROPERTY(BlueprintReadOnly)
	float distanceTraveled = 0.0f;

	FVector lastTickLocation;

	FVector spawnScale; //stores the spawn scale

	//UProperties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float impactDamage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float hitImpulse = 100.0f;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	bool bDrawDebug = false;

	//COMPONENTS
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
	//USceneComponent * sceneRootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
	UStaticMeshComponent * collisionMeshComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		class UProjectileMovementComponent* projectileMovement;


	virtual void BeginPlay() override;

	//Disable Movement and Collision, only for cosmetics
	void SetDummy();

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UPROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	bool bInitIsDummy = false;

	AProjectile();

	virtual void OnConstruction(const FTransform& Transform) override;

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintImplementableEvent, Category = "Projectile")
	void OnImpact(const FHitResult& Hit);

	UFUNCTION()
	void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class UStaticMeshComponent* GetCollisionMeshComp() const { return collisionMeshComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return projectileMovement; }

//Projectile Effects
	UFUNCTION(BlueprintCallable)
	UProjectileEffectClass* AddEffect(TSubclassOf<UProjectileEffectClass> newEffect);

	UFUNCTION(BlueprintCallable)
	UProjectileEffectBase* AddProjectileEffect(TSubclassOf<UProjectileEffectBase> newEffect);

	UFUNCTION(BlueprintCallable)
	void SplitProjectile(TSubclassOf<AProjectile> projectile_BP);

	UFUNCTION(BlueprintCallable)
	void UpdateScaleByTraceDistance(float scalor = 0.0001f);
};



UCLASS()
class BOWROGUE_API USplitEffectClass : public UProjectileEffectClass {
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> splitProjectile_BP;

public:
	USplitEffectClass() {}
	

	//virtual void Tick(float deltaTime) {}
	virtual void OnHit(const FHitResult& hitResult) override {
		FTransform trans;
		trans.SetLocation(mainProjectile->GetActorLocation());
		trans.SetRotation(mainProjectile->GetActorRightVector().ToOrientationQuat());
		trans.SetScale3D(mainProjectile->GetActorScale3D() * 0.5f);

		mainProjectile->GetWorld()->SpawnActor<AProjectile>(splitProjectile_BP, trans);

		trans.SetRotation((mainProjectile->GetActorRightVector() * -1.0f).ToOrientationQuat());
		mainProjectile->GetWorld()->SpawnActor<AProjectile>(splitProjectile_BP, trans);
	}
};