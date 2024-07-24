// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS_StudyGameplayAbility.h"
#include "Actor/GAS_StudyRocketProjectile.h"
#include "GAS_StudyRocketAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_STUDY_API UGAS_StudyRocketAbility : public UGAS_StudyGameplayAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void SpawnRocket();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGAS_StudyRocketProjectile> RocketProjectileClass;
};
