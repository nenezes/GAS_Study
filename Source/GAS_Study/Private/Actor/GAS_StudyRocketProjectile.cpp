// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.


#include "..\..\Public\Actor\GAS_StudyRocketProjectile.h"

#include "..\..\Public\Actor\GAS_StudyExplosion.h"
#include "GameFramework/ProjectileMovementComponent.h"


AGAS_StudyRocketProjectile::AGAS_StudyRocketProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	// Construct base components
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	// Configure sphere's collision settings to overlap with all channels
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AGAS_StudyRocketProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Bind OnComponentBeginOverlap to OnSphereOverlap function
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGAS_StudyRocketProjectile::OnSphereOverlap);
}

void AGAS_StudyRocketProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner() || !HasAuthority())
	{
		return;
	}

	// Spawn Explosion Actor

	const FTransform SpawnTransform = GetActorTransform();
	
	GetWorld()->SpawnActor<AGAS_StudyExplosion>(AGAS_StudyExplosion::StaticClass(), SpawnTransform);
	
	Destroy();
}

