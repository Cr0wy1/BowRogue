// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StageActor.generated.h"



class ADungeon;



UCLASS()
class BOWROGUE_API AStageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStageActor();

protected:

	TArray<ADungeon*> dungeons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADungeon> dungeonDefaultBP;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartStage();

	void EndStage();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
