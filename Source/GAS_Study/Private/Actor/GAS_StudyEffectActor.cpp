// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.

#include "Actor/GAS_StudyEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


AGAS_StudyEffectActor::AGAS_StudyEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AGAS_StudyEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGAS_StudyEffectActor::ApplyInstantGameplayEffect(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffect)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);

	if (TargetASC == nullptr)
	{
		return;
	}

	check(GameplayEffect);
	
	const FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffect, 1.f, ContextHandle);
	TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

