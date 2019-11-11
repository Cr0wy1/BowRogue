// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedWidget.h"
#include "HealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOWROGUE_API UHealthWidget : public UAdvancedWidget
{
	GENERATED_BODY()

	UPROPERTY( meta = (BindWidget))
	class UProgressBar* healthBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* healthText;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* staminaBar;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* staminaText;

protected:

public:

	void UpdateHealth(float healthAmount, float maxHealthAmount);
	void UpdateStamina(float staminaAmount, float maxStaminaAmount);
};
