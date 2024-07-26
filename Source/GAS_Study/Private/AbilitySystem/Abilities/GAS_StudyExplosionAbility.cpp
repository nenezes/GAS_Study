// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.


#include "AbilitySystem/Abilities/GAS_StudyExplosionAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Actor/GAS_StudyExplosion.h"
#include "Engine/OverlapResult.h"


void UGAS_StudyExplosionAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!HasAuthority(&ActivationInfo))
	{
		return;
	}
	
	TriggerExplosion(ActivationInfo);
}

void UGAS_StudyExplosionAbility::TriggerExplosion(const FGameplayAbilityActivationInfo& ActivationInfo) const
{
	const FVector ExplosionLocation = GetOwningActorFromActorInfo()->GetActorLocation();
	
	const FCollisionQueryParams SphereColParams(SCENE_QUERY_STAT(ApplyRadialDamage), false, GetOwningActorFromActorInfo());

	TArray<FOverlapResult> OverlapResults;
	
	if (const UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(
			OverlapResults, ExplosionLocation,
			FQuat::Identity,
			FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects),
			FCollisionShape::MakeSphere(ExplosionRadius),
			SphereColParams);
	}

	TArray<UAbilitySystemComponent*> DamagedASCArray = TArray<UAbilitySystemComponent*>();

	for (auto& OverlapObject : OverlapResults)
	{
		AActor* OverlapActor = OverlapObject.OverlapObjectHandle.FetchActor();

		if (!IsValid(OverlapActor))
		{
			continue;
		}
		
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OverlapActor);
		
		if (!IsValid(TargetASC) || DamagedASCArray.Contains(TargetASC))
		{
			continue;
		}

		if (!IsValid(ExplosionDamageEffect))
		{
			return;
		}
		
		const FGameplayEffectSpecHandle DamageEffectSpec = TargetASC->MakeOutgoingSpec(
		ExplosionDamageEffect, 1.f, TargetASC->MakeEffectContext());
		TargetASC->ApplyGameplayEffectSpecToTarget(*DamageEffectSpec.Data.Get(), TargetASC);

		DamagedASCArray.Add(TargetASC);
	}
}