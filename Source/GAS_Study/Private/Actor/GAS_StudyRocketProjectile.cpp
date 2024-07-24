// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.


#include "..\..\Public\Actor\GAS_StudyRocketProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"


AGAS_StudyRocketProjectile::AGAS_StudyRocketProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	// Construct base components
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	// Configure sphere's collision settings to only overlap with WorldStatic and Pawns
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
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
	if (OtherActor == GetOwner())
	{
		return;
	}

	//Spawn Explosion Actor
	
	Destroy();
}

