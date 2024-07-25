// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.


#include "Actor/GAS_StudyExplosion.h"

#include "AbilitySystemComponent.h"
#include "Character/GAS_StudyCharacter.h"


AGAS_StudyExplosion::AGAS_StudyExplosion()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	// Construct base components
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetSphereRadius(ExplosionRadius);
	SetRootComponent(Sphere);

	// Configure sphere's collision settings to overlap with all channels
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AGAS_StudyExplosion::BeginPlay()
{
	Super::BeginPlay();

	// Bind OnComponentBeginOverlap to OnSphereOverlap function
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGAS_StudyExplosion::OnSphereOverlap);
}

void AGAS_StudyExplosion::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                          const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}

	const AGAS_StudyCharacter* TargetCharacter = Cast<AGAS_StudyCharacter>(OtherActor);
	
	if (!IsValid(TargetCharacter))
	{
		return;
	}

	UAbilitySystemComponent* TargetASC = TargetCharacter->GetAbilitySystemComponent();

	if (!IsValid(TargetASC) || DamagedTargetASCArray.Contains(TargetASC))
	{
		return;
	}

	const FGameplayEffectSpecHandle DamageEffectSpec = TargetASC->MakeOutgoingSpec(
		ExplosionDamageEffect, 1.f, TargetASC->MakeEffectContext());
	TargetASC->ApplyGameplayEffectSpecToTarget(*DamageEffectSpec.Data.Get(), TargetASC);

	DamagedTargetASCArray.Add(TargetASC);

	
}
