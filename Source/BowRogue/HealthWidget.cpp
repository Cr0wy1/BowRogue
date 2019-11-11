// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"
#include "TextBlock.h"
#include "ProgressBar.h"

void UHealthWidget::UpdateHealth(float healthAmount, float maxHealthAmount){
	float percent = healthAmount / maxHealthAmount;
	healthBar->SetPercent(percent);
	healthText->SetText(FText::FromString(FString::FromInt(healthAmount) + "/" + FString::FromInt(maxHealthAmount)));
}

void UHealthWidget::UpdateStamina(float staminaAmount, float maxStaminaAmount){
	float percent = staminaAmount / maxStaminaAmount;
	staminaBar->SetPercent(percent);
	staminaText->SetText(FText::FromString(FString::FromInt(staminaAmount) + "/" + FString::FromInt(maxStaminaAmount)));
}
