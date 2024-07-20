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
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	EGameplayEffectDurationType GameplayEffectDurationType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects", meta = (EditCondition = "GameplayEffectDurationType == EGameplayEffectDurationType::Infinite"))
	bool bRemoveOnEndOverlap = true;
	
	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* OtherActor);
	
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* OtherActor);

	//Apply a gameplay effect to a target actor
	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffect(AActor* Target, const TSubclassOf<UGameplayEffect> GameplayEffect);

	//Map to track applied active effect handles and possibly execute logic on end overlap
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
};
