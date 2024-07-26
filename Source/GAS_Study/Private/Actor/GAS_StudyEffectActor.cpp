// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.

#include "Actor/GAS_StudyEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"


AGAS_StudyEffectActor::AGAS_StudyEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AGAS_StudyEffectActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
}

void AGAS_StudyEffectActor::StartCooldown()
{
	Cooldown = RegenerationTime;
	bCanInteract = false;
	SetActorHiddenInGame(true);
}

void AGAS_StudyEffectActor::EndCooldown()
{
	bCanInteract = true;
	SetActorHiddenInGame(false);
}

void AGAS_StudyEffectActor::OnCooldown()
{
	--Cooldown;
	
	if (Cooldown <= 0)
	{
		EndCooldown();
		GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
	}
}

void AGAS_StudyEffectActor::OnBeginOverlap(AActor* OtherActor)
{
	if (!HasAuthority())
	{
		return;
	}

	if (bCanInteract)
	{
		ApplyGameplayEffect(OtherActor, GameplayEffectClass);
	}

	if (bDestroyAfterPickup)
	{
		Destroy();
	}

	if (bRegenAfterPickup && bCanInteract)
	{
		StartCooldown();
		GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &AGAS_StudyEffectActor::OnCooldown, 1.f, true);
	}
}

void AGAS_StudyEffectActor::OnEndOverlap(AActor* OtherActor)
{
	if (!HasAuthority())
	{
		return;
	}
	
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);

	TArray<FActiveGameplayEffectHandle> HandlesToRemove;

	//If the effect is infinite and should be removed on end overlap, loops through the ActiveEffectHandles and adds the applied handle to the HandlesToRemove array
	if (GameplayEffectDurationType == EGameplayEffectDurationType::Infinite && bRemoveOnEndOverlap)
	{
		for (auto HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
	}

	//Remove inactive handles from the ActiveEffectHandles map 
	for (auto& Handle : HandlesToRemove)
	{
		ActiveEffectHandles.FindAndRemoveChecked(Handle);
	}
}

void AGAS_StudyEffectActor::ApplyGameplayEffect(AActor* Target, const TSubclassOf<UGameplayEffect> GameplayEffect)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);

	if (TargetASC == nullptr)
	{
		return;
	}

	check(GameplayEffect);
	
	const FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffect, 1.f, ContextHandle);
	const FActiveGameplayEffectHandle ActiveHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
	//Add the active effect handle to a map if it should be removed on end overlap and if it is an infinite gameplay effect
	if (bRemoveOnEndOverlap && SpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite)
	{
		ActiveEffectHandles.Add(ActiveHandle, TargetASC);
	}
}

