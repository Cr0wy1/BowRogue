// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionBoxActor.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"



// Sets default values
ADirectionBoxActor::ADirectionBoxActor(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sceneComp = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = sceneComp;

	boxComp = CreateDefaultSubobject<UBoxComponent>("Box");
	boxComp->SetCollisionProfileName("DirectionObject");
	boxComp->SetBoxExtent(FVector(boxSize));
	boxComp->SetRelativeLocation(FVector(boxSize));
	boxComp->SetupAttachment(sceneComp);
	//boxComp->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel6);
	//boxComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//boxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel6, ECollisionResponse::ECR_Ignore);


	arrowComp = CreateDefaultSubobject<UArrowComponent>("Arrow");
	arrowComp->SetRelativeLocation(FVector(-160.0f, 0, 0));
	arrowComp->ArrowSize = 4.0f;
	arrowComp->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ADirectionBoxActor::BeginPlay(){
	Super::BeginPlay();
	
}

// Called every frame
void ADirectionBoxActor::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

FVector ADirectionBoxActor::GetDirection() const{
	return arrowComp->GetComponentRotation().Vector();
}

