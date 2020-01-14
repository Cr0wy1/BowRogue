// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryPawn.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AGeometryPawn::AGeometryPawn(){
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//sceneComp = CreateDefaultSubobject<USceneComponent>("Scene");
	//RootComponent = sceneComp;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = meshComp;
	//meshComp->SetupAttachment(sceneComp);
	
}

// Called when the game starts or when spawned
void AGeometryPawn::BeginPlay(){
	Super::BeginPlay();
	
}

// Called every frame
void AGeometryPawn::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	//Update Actors Location based on meshComponent
	SetActorLocation(meshComp->GetComponentLocation());

	//meshComp->AddForce(constantForce);
	//meshComp->AddRelativeLocation(constantVelocity, true, nullptr);

	FVector min, max;
	meshComp->GetLocalBounds(min, max);

	//meshComp->AddForceAtLocationLocal(constantForce, min);
	//meshComp->AddForceAtLocationLocal(-constantForce, max);
	
}

float AGeometryPawn::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser){

	UE_LOG(LogTemp, Warning, TEXT("%s: DamageTaken(%f)"), *GetName(), DamageAmount);

	return 0.0f;
}

void AGeometryPawn::AddRotateImpulse(float amount){
	FVector min, max;
	meshComp->GetLocalBounds(min, max);

	meshComp->AddImpulseAtLocation(FVector(amount, 0, 0), FVector(min.X, min.Y, 0) );
	meshComp->AddImpulseAtLocation(FVector(-amount, 0, 0), FVector(max.X, max.Y, 0));
}

void AGeometryPawn::JumpAtDirection(FVector direction, float impulseAmount, float heightAmount){
	direction.Z = heightAmount;
	direction.Normalize();
	direction *= impulseAmount;
	
	meshComp->AddImpulse(direction);
}

void AGeometryPawn::JumpToTargetLocation(float impulseAmount, float heightAmount){
	FVector direction = targetLocation - GetActorLocation();
	direction.Normalize();

	JumpAtDirection(direction, impulseAmount, heightAmount);
}


