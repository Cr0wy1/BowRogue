// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedWidget.h"
#include "GameStructs.h"
#include "PlayerHUDWidget.generated.h"



class UTextBlock;
/**
 * 
 */
UCLASS()
class BOWROGUE_API UPlayerHUDWidget : public UAdvancedWidget
{
	GENERATED_BODY()

protected:

	class UAttributeComponent* attrComp;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* interactText;

	UFUNCTION()
	void OnHealthUpdate();

	UFUNCTION()
	void OnAttributeUpdate();

public:

	UPROPERTY(meta = (BindWidget))
	class UHealthWidget * healthWidget;

	UFUNCTION()
	void OnStaminaUpdate();

	UFUNCTION(BlueprintCallable)
	void Init(class UAttributeComponent* _attrComp);

	void SetInteractText(bool visible, FText text = FText::FromString("Press 'E'") );
};
