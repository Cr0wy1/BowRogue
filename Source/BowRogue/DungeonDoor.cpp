// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonDoor.h"
#include "Components/StaticMeshComponent.h"
#include "BowRogueCharacter.h"

// Sets default values
ADungeonDoor::ADungeonDoor(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->OnComponentHit.AddDynamic(this, &ADungeonDoor::OnHit);
}

// Called when the game starts or when spawned
void ADungeonDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADungeonDoor::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit){
	
	ABowRogueCharacter* player = Cast<ABowRogueCharacter>(OtherActor);
	if (player) {
		UE_LOG(LogTemp, Warning, TEXT("Door Hit!"));

		player->AddActorWorldOffset(-GetActorForwardVector()*200.0f);
		//player->SetActorLocation( )
	}
}

// Called every frame
void ADungeonDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

