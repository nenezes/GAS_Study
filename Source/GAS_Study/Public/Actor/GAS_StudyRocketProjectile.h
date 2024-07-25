// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS_StudyExplosion.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GAS_StudyRocketProjectile.generated.h"


class UProjectileMovementComponent;

UCLASS()
class GAS_STUDY_API AGAS_StudyRocketProjectile : public AActor
{
	GENERATED_BODY()

public:
	
	AGAS_StudyRocketProjectile();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float ExplosionRadius = 500.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> ExplosionDamageEffect;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                     int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	void TriggerExplosion();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	
};
