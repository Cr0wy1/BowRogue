// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedSceneComponent.h"


// Sets default values for this component's properties
UAdvancedSceneComponent::UAdvancedSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UAdvancedSceneComponent::BeginPlay(){
	Super::BeginPlay();

	baseRotation = GetComponentRotation();
	
}


// Called every frame
void UAdvancedSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateRotation();
}


void UAdvancedSceneComponent::UpdateRotation(){

	FRotator newRotation = GetComponentRotation();

	if (!bInheritPitch) {
		newRotation.Pitch = baseRotation.Pitch;
	}
	if (!bInheritRoll) {
		newRotation.Roll = baseRotation.Roll;
	}
	if (!bInheritYaw) {
		newRotation.Yaw = baseRotation.Yaw;
	}

	SetWorldRotation(newRotation);
}
