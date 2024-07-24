// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.


#include "AbilitySystem/Abilities/GAS_StudyRocketAbility.h"

#include "Character/GAS_StudyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

void UGAS_StudyRocketAbility::SpawnRocket()
{
	// Check for server authority
	if (!GetOwningActorFromActorInfo()->HasAuthority())
	{
		return;
	}

	// Cache the spawn location
	FTransform SpawnTransform;
	AGAS_StudyCharacter* Character = Cast<AGAS_StudyCharacter>(GetAvatarActorFromActorInfo());
	SpawnTransform.SetLocation(Character->GetHandSocketLocation());

	// Spawn actor deferred to set target direction before we finish spawning
	AGAS_StudyRocketProjectile* RocketProjectile = GetWorld()->SpawnActorDeferred<AGAS_StudyRocketProjectile>(
		RocketProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	//TODO: Set target direction
	
	RocketProjectile->FinishSpawning(SpawnTransform);
}

void UGAS_StudyRocketAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
}
