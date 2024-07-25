// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GAS_StudyExplosion.generated.h"

class UGameplayEffect;

UCLASS()
class GAS_STUDY_API AGAS_StudyExplosion : public AActor
{
	GENERATED_BODY()

public:
	
	AGAS_StudyExplosion();

protected:
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(EditAnywhere)
	float ExplosionRadius = 500.f;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> ExplosionDamageEffect;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY()
	TArray<TObjectPtr<UAbilitySystemComponent>> DamagedTargetASCArray;
};
