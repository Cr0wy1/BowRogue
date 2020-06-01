// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaneTraceComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "ConstructorHelpers.h"

// Sets default values for this component's properties 
UPlaneTraceComponent::UPlaneTraceComponent(){
	PrimaryComponentTick.bCanEverTick = true;
	
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}


// Called when the game starts
void UPlaneTraceComponent::BeginPlay(){
	Super::BeginPlay();

	
}

FHitResult UPlaneTraceComponent::TraceLine(const FVector & location){
	FHitResult hitResult;
	GetWorld()->LineTraceSingleByChannel(hitResult, location, location + FVector(0, 0, -1000), ECollisionChannel::ECC_WorldStatic);

	return hitResult;
}

bool UPlaneTraceComponent::TraceCheck(float &checkedDifference, float maxDifference){

	float difference = 0.0f;

	for (FName socketName : GetAllSocketNames()) {

		FVector location = GetSocketLocation(socketName);
		FHitResult hitResult = TraceLine(location);

		difference += (hitResult.Location - location).Size();

		if (bDrawDebug) {
			DrawLines(location);
			DrawDebugPoint(GetWorld(), hitResult.Location, 20.0f, FColor::Red, true, -1.0f);
		}
		
	}

	checkedDifference = difference;

	if (difference < maxDifference) {
		return true;
	}
	
	return false;
}



// Called every frame
void UPlaneTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//TraceCheck();
}

void UPlaneTraceComponent::DrawLines(const FVector &location){
	UE_LOG(LogTemp, Warning, TEXT("draw"));

	DrawDebugLine(GetWorld(), location, location + FVector(0, 0, -1000), FColor::Green, true, -1.0f, 0, 4.0f);

	/*
	FlushPersistentDebugLines(GetWorld());

	FVector corner1 = FVector(min.X, min.Y, 0);
	FVector corner2 = FVector(min.X, max.Y, 0);
	FVector corner3 = FVector(max.X, min.Y, 0);
	FVector corner4 = FVector(max.X, max.Y, 0);

	//UE_LOG(LogTemp, Warning, TEXT("corner1: %s"), *corner1.ToCompactString());


	DrawDebugLine(GetWorld(), corner1, corner1 + FVector(0, 0, -100), FColor::Green, true, -1.0f, 0, 10.0f);
	DrawDebugLine(GetWorld(), corner2, corner2 + FVector(0, 0, -100), FColor::Green, true, -1.0f, 0, 10.0f);
	DrawDebugLine(GetWorld(), corner3, corner3 + FVector(0, 0, -100), FColor::Green, true, -1.0f, 0, 10.0f);
	DrawDebugLine(GetWorld(), corner4, corner4 + FVector(0, 0, -100), FColor::Green, true, -1.0f, 0, 10.0f);

	FVector extent = FVector(min.GetAbs() + max, 0);
	FVector center = (extent / 2) + FVector(min, 0);

	DrawDebugBox(GetWorld(), center, extent / 2, FColor::Red, true, -1.0f, 0, 10.0f);
	*/
}

