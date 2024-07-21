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

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGAS_StudyExplosion> ExplosionClass;
};
