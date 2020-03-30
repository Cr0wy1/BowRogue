// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectBase.h"
#include "Projectiles/Projectile.h"

void UProjectileEffectBase::Init(AProjectile * _projectile){
	projectile = _projectile;
}

//ProjectileEffectManager
void FProjectileEffectManager::CallAllOnHit(const FHitResult & hitResult) {
	for (auto effect : effects) {
		effect->OnHit(hitResult);
	}
}

void FProjectileEffectManager::CallAllOnTick(float deltaTime) {
	for (auto effect : effects) {
		effect->OnTick(deltaTime);
	}
}

void FProjectileEffectManager::CallAllOnSpawn() {
	for (auto effect : effects) {
		effect->OnSpawn();
	}
}

bool FProjectileEffectManager::HasEffect(const FName& effectName) const{
	for (auto effect : effects) {
		if (effect->HasEqualName(effectName)) {
			return true;
		}
	}
	return false;
}

bool FProjectileEffectManager::HasEffect(const UProjectileEffectBase * checkEffect) const{
	for (auto effect : effects) {
		if (effect->HasEqualName(checkEffect)) {
			return true;
		}
	}
	return false;
}
