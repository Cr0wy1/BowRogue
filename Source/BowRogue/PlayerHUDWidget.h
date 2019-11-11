// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedWidget.h"
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
	UPROPERTY(meta = (BindWidget))
	UTextBlock* interactText;

public:

	void SetInteractText(bool visible, FText text = FText::FromString("Press 'E'") );
};
