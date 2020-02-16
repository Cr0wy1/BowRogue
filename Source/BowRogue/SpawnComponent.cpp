// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnComponent.h"
#include "DrawDebugHelpers.h"
#include "GeometryPawn.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USpawnComponent::USpawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	

	
	FlushPersistentDebugLines(GetWorld());

	if (geoPawn) {
		GetWorld()->SpawnActor<AGeometryPawn>(geoPawn, GetComponentLocation(), FRotator(0));
	}
	
}


// Called when the game starts
void USpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	
} 

void USpawnComponent::PostEditComponentMove(bool bFinished){


	Super::PostEditComponentMove(bFinished);
}

void USpawnComponent::OnRegister(){
	Super::OnRegister();


}

