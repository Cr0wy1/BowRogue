// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop.h"
#include "DestructibleComponent.h"

// Sets default values
AProp::AProp()
{
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	destructibleComp = CreateDefaultSubobject<UDestructibleComponent>("Destructible");
	
}

// Called when the game starts or when spawned
void AProp::BeginPlay(){
	Super::BeginPlay();
	destructibleComp->OnComponentHit.AddDynamic(this, &AProp::OnHit);	
}

void AProp::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit){
	UE_LOG(LogTemp, Warning, TEXT("Prop: i am hitted"));

	destructibleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	destructibleComp->ApplyDamage(10.0f, Hit.ImpactPoint, NormalImpulse, 100.0f);
	
	//SetLifeSpan(5.0f);
}

// Called every frame
void AProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


