// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.


#include "..\..\Public\Actor\GAS_StudyRocketProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/GAS_StudyAbilitySystemComponent.h"
#include "Engine/OverlapResult.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"


AGAS_StudyRocketProjectile::AGAS_StudyRocketProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AGAS_StudyRocketProjectile::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGAS_StudyRocketProjectile::OnSphereOverlap);
}

void AGAS_StudyRocketProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                 const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner())
	{
		return;
	}
	
	TriggerExplosion();

	if (!HasAuthority())
	{
		return;
	}

	Destroy();
}

void AGAS_StudyRocketProjectile::TriggerExplosion()
{
	const FVector ExplosionLocation = GetActorLocation();
	
	TriggerExplosionEffects(ExplosionLocation);

	if (!HasAuthority())
	{
		return;
	}
	
	const FCollisionQueryParams SphereColParams(SCENE_QUERY_STAT(ApplyRadialDamage), false, GetOwner());

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

		const FGameplayEffectSpecHandle DamageEffectSpec = TargetASC->MakeOutgoingSpec(
		ExplosionDamageEffect, 1.f, TargetASC->MakeEffectContext());
		TargetASC->ApplyGameplayEffectSpecToTarget(*DamageEffectSpec.Data.Get(), TargetASC);

		DamagedASCArray.Add(TargetASC);
	}
}

void AGAS_StudyRocketProjectile::TriggerExplosionEffects(const FVector& ExplosionLocation) const
{
	if (UNiagaraSystem* NiagaraSystem = ExplosionNiagaraSystem; IsValid(NiagaraSystem))
	{		
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, NiagaraSystem, ExplosionLocation);
	}
}
