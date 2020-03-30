// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EffectComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Player/AdvancedCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UEffectComponent::UEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	character = Cast<AAdvancedCharacter>(GetOwner());

	timeManager = &GetWorld()->GetTimerManager();
	
	//AddEffect(new FEffectDataFreeze(character));
}


// Called every frame
void UEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UEffectComponent::AddEffect(FEffectData* effectData){
	if (!effectData) return;
	FEffectHandle* effectHandle = &effectHandles.Emplace_GetRef(effectData);

	FTimerDelegate endEffectDelegate = FTimerDelegate::CreateUObject(this, &UEffectComponent::EndEffect, *effectHandle);
	timeManager->SetTimer(timer, endEffectDelegate, effectData->duration, false);
	effectHandle->data->Start();
}

void UEffectComponent::EndEffect(FEffectHandle effectHandle){
	if (effectHandle.data) {
		effectHandle.data->End();
	}
	
}


void FEffectData::Init(AAdvancedCharacter * _character){
	character = _character;
}

void FEffectData::Start() {
	UE_LOG(LogTemp, Warning, TEXT("Start Effect!"));

}

void FEffectData::End() {
	UE_LOG(LogTemp, Warning, TEXT("End Effect!"));

}


void FEffectDataFreeze::Start(){
	FEffectData::Start();

	baseWalkSpeed = character->GetCharacterMovement()->MaxWalkSpeed;
	character->GetCharacterMovement()->MaxWalkSpeed = 0.0f;
}

void FEffectDataFreeze::End(){
	FEffectData::End();

	character->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}
