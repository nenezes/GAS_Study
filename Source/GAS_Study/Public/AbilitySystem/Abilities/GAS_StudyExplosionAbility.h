// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS_StudyGameplayAbility.h"
#include "Actor/GAS_StudyExplosion.h"
#include "GAS_StudyExplosionAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_STUDY_API UGAS_StudyExplosionAbility : public UGAS_StudyGameplayAbility
{
	GENERATED_BODY()

protected:
	/** Called when ability is activated */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	/** Only triggered on server */
	void TriggerExplosion(const FGameplayAbilityActivationInfo& ActivationInfo) const;

	/** Radius of explosion */
	UPROPERTY(EditDefaultsOnly)
	float ExplosionRadius = 500.f;

	/** Explosion damage effect class */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> ExplosionDamageEffect;

	/** Array of Ability System Components that were already damaged by the explosion */
	UPROPERTY()
	TArray<TObjectPtr<UAbilitySystemComponent>> DamagedTargetASCArray;
};
