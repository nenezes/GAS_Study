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

	// Try to fire towards an World position, if not able to find one, fire in direction of camera rotation
	FHitResult Hit;
	const APlayerCameraManager* CameraManager = Cast<APlayerController>(Character->GetController())->PlayerCameraManager;

	const FVector StartLocation = CameraManager->GetCameraLocation();
	const FVector CameraForward = CameraManager->GetCameraRotation().Vector();
	const FVector EndLocation = StartLocation + CameraForward * FLT_MAX;

	if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility))
	{
		const FRotator Rotation = (Hit.Location - SpawnTransform.GetLocation()).Rotation();
		SpawnTransform.SetRotation(Rotation.Quaternion());
	}
	else
	{
		SpawnTransform.SetRotation(CameraManager->GetCameraRotation().Quaternion());
	}
	
	// Spawn actor deferred to set target direction before we finish spawning
	AGAS_StudyRocketProjectile* RocketProjectile = GetWorld()->SpawnActorDeferred<AGAS_StudyRocketProjectile>(
		RocketProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	
	RocketProjectile->FinishSpawning(SpawnTransform);
}

void UGAS_StudyRocketAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
}
