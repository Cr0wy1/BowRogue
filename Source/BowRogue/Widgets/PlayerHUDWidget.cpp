// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"
#include "Widgets/HealthWidget.h"
#include "TextBlock.h"
#include "Components/HealthComponent.h"



void UPlayerHUDWidget::Init(UHealthComponent * _healthComp){
	healthComp = _healthComp;
	if (!healthComp) {
		UE_LOG(LogTemp, Warning, TEXT("UPlayerHUDWidget: attrComp is nullptr"));
	}
}

void UPlayerHUDWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime){
	OnHealthUpdate();
	OnStaminaUpdate();
}

void UPlayerHUDWidget::OnHealthUpdate() {
	//UE_LOG(LogTemp, Warning, TEXT("Widget Health: %s"), *attrComp->health->ToString());

	healthWidget->UpdateHealth(healthComp->GetHealth().GetValue(), healthComp->GetHealth().GetMax());
}
void UPlayerHUDWidget::OnAttributeUpdate(){
	OnHealthUpdate();
	OnStaminaUpdate();
}


void UPlayerHUDWidget::OnStaminaUpdate(){
	healthWidget->UpdateStamina(healthComp->GetStamina().value, healthComp->GetStamina().max);
}

void UPlayerHUDWidget::SetInteractText(bool visible, FText text){
	if (visible) {
		interactText->SetText(text);
		interactText->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else {
		interactText->SetVisibility(ESlateVisibility::Collapsed);
	}
	
}
