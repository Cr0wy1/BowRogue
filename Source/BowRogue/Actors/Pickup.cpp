// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Player/AdvancedCharacter.h"
#include "Engine/World.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Detection Sphere"));
	RootComponent = sphereComp;
	sphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	meshComp->SetupAttachment(sphereComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	if(bAdjustMeshToSphere && meshComp->GetStaticMesh() ) {
		AdjustMeshToSphere(bAdjustBorderSpace);
	}
	
}


// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::Take(AAdvancedCharacter* character){
	UE_LOG(LogTemp, Warning, TEXT("Pick up taken"));

	Destroy();
}

void APickup::SetItem(FItemData * _itemData){
	if (_itemData && _itemData->mesh) {
		itemData = _itemData;
		meshComp->SetStaticMesh(itemData->mesh);
		if (bAdjustMeshToSphere) {
			AdjustMeshToSphere(bAdjustBorderSpace);
		}
	}
}

APickup * APickup::Construct(AActor* constructor, const FVector & location, FItemData * itemData){
	
	if (!constructor) {
		UE_LOG(LogTemp, Warning, TEXT("APickup::Construct: owner is nullptr"));
		return nullptr;
	}

	if (!itemData) {
		UE_LOG(LogTemp, Warning, TEXT("APickup::Construct: itemData is nullptr"));
		return nullptr;
	}


	APickup* pickup = constructor->GetWorld()->SpawnActor<APickup>(location, FRotator::ZeroRotator);
	pickup->SetItem(itemData);
	return pickup;
}

APickup * APickup::Construct(AActor * constructor, const FVector & location, UDataTable* dataTable, FName rowName){
	return Construct(constructor, location, FItemData::FromId(dataTable, rowName));
}

void APickup::AdjustMeshToSphere(float borderSpace) {
	FVector boundMin, boundMax;
	meshComp->GetLocalBounds(boundMin, boundMax);
	FVector deltaBound = boundMin + boundMax;

	float maxAxeLength = (boundMin.GetAbs() + boundMax.GetAbs()).GetMax();
	float sphereDia = (sphereComp->GetScaledSphereRadius() - borderSpace) * 2.0f;
	float scalorFactor = sphereDia / maxAxeLength;

	//Center Mesh by bounding box origin
	meshComp->SetRelativeLocation(-(deltaBound*scalorFactor*0.5f));

	//scale mesh to sphere border
	meshComp->SetWorldScale3D(FVector(scalorFactor));
	

	//UE_LOG(LogTemp, Warning, TEXT("Pickup Bounds: Min:%s, Max:%s"), *boundMin.ToCompactString(), *boundMax.ToCompactString());
	//UE_LOG(LogTemp, Warning, TEXT("Pickup maxAxeLength:%f sphereRadius:%f"), maxAxeLength, sphereDia);
}

