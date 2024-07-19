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

	UPROPERTY(EditAnywhere, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> InstanceGameplayEffect;

	UFUNCTION(BlueprintCallable)
	void ApplyInstantGameplayEffect(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffect);
};
