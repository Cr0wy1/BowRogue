// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/ItemUpdateStructs.h"
#include "Projectile.generated.h"




UCLASS()
class BOWROGUE_API AProjectile : public AActor
{
	GENERATED_BODY()


protected:


	UPROPERTY(BlueprintReadOnly)
	int32 bounceCounter;

	UPROPERTY(BlueprintReadOnly)
	float distanceTraveled = 0.0f;

	FVector lastTickLocation;

	FVector spawnScale; //stores the spawn scale

public:
	//UProperties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float impactDamage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float hitImpulse = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float weight = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float speed = 3000.0f;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	bool bDrawDebug = false;

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

	void UpdateProjectile(const FProjectileUpdate &projectileUpdate);

	void UpdateAttribute(const FProjectileAttributeUpdate &projectileAttribute);

	//void ShouldBounce(bool shouldBounce){ projectileMovement }
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
	void SplitProjectile(TSubclassOf<AProjectile> projectile_BP);

	UFUNCTION(BlueprintCallable)
	void UpdateScaleByTraceDistance(float scalor = 0.0001f);
};







UCLASS()
class BOWROGUE_API USplitEffectClass : public UProjectileEffectBase {
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> splitProjectile_BP;

public:
	USplitEffectClass() {}
	

	//virtual void Tick(float deltaTime) {}
	virtual void OnHit(const FHitResult& hitResult) override {
		FTransform trans;
		trans.SetLocation(projectile->GetActorLocation());
		trans.SetRotation(projectile->GetActorRightVector().ToOrientationQuat());
		trans.SetScale3D(projectile->GetActorScale3D() * 0.5f);

		projectile->GetWorld()->SpawnActor<AProjectile>(splitProjectile_BP, trans);

		trans.SetRotation((projectile->GetActorRightVector() * -1.0f).ToOrientationQuat());
		projectile->GetWorld()->SpawnActor<AProjectile>(splitProjectile_BP, trans);
	}
};