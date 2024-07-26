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

	/** Called when projectile hits something */
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                     int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	/** Triggers explosion on server and client */
	void TriggerExplosion();

	/** Triggers explosion effects (SFX and VFX) on client */
	void TriggerExplosionEffects(const FVector& ExplosionLocation) const;

	/** Radius of explosion */
	UPROPERTY(EditDefaultsOnly)
	float ExplosionRadius = 500.f;

	/** Explosion damage Gameplay Effect class */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> ExplosionDamageEffect;

	/** Explosion Niagara System class */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> ExplosionNiagaraSystem;

	/** Sphere component used to detect impact point */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	/** Projectile movement component used to move the projectile */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	
};
