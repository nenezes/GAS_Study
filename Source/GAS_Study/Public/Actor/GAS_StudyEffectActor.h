// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "GAS_StudyEffectActor.generated.h"


UCLASS()
class GAS_STUDY_API AGAS_StudyEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AGAS_StudyEffectActor();

protected:
	
	/** Gameplay effect class to apply */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	/** Duration type of the gameplay effect */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	EGameplayEffectDurationType GameplayEffectDurationType;

	/** Should the effect be removed on end overlap? */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects", meta = (EditCondition = "GameplayEffectDurationType == EGameplayEffectDurationType::Infinite"))
	bool bRemoveOnEndOverlap = true;

	/** Called on end play to clean up timer handle */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	/** Starts the cooldown state of the Effect Actor */
	void StartCooldown();

	/** Ends the cooldown state of the Effect Actor */
	void EndCooldown();

	/** Handles cooldown logic */
	void OnCooldown();

	/** Called when the actor begins overlap with another actor */
	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* OtherActor);

	/** Called when the actor ends overlap with another actor */
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* OtherActor);

	/** Apply the gameplay effect to the target actor */
	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffect(AActor* Target, const TSubclassOf<UGameplayEffect> GameplayEffect);

	/** Should the actor regen after it is picked up? */
	UPROPERTY(EditAnywhere, Category = "Effect Actor")
	bool bRegenAfterPickup = false;
	
	/** Should the actor be destroyed after it is picked up? */
	UPROPERTY(EditAnywhere, Category = "Effect Actor")
	bool bDestroyAfterPickup = false;

	/** Time in seconds to regenerate the actor */
	UPROPERTY(EditAnywhere, Category = "Effect Actor")
	int32 RegenerationTime = 5;

	/** Timer handle for cooldown */
	FTimerHandle CooldownTimerHandle;
	
	/** Current cooldown time */
	UPROPERTY(EditAnywhere, Category = "Effect Actor")
	int32 Cooldown = 0;

	/** Can the actor be picked up? */
	bool bCanInteract = true;

	/** Map to track applied active effect handles and possibly execute logic on end overlap */
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
};
