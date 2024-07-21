// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.


#include "AbilitySystem/Abilities/GAS_StudyExplosionAbility.h"

#include "Actor/GAS_StudyExplosion.h"

void UGAS_StudyExplosionAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!HasAuthority(&ActivationInfo))
	{
		return;
	}
	
	FTransform SpawnTransform = GetOwningActorFromActorInfo()->GetTransform();

	AGAS_StudyExplosion* Explosion = GetWorld()->SpawnActorDeferred<AGAS_StudyExplosion>(
		ExplosionClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);


	
	Explosion->FinishSpawning(SpawnTransform);
}
