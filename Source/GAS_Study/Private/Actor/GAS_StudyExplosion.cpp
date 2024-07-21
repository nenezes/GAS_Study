// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.


#include "Actor/GAS_StudyExplosion.h"


AGAS_StudyExplosion::AGAS_StudyExplosion()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void AGAS_StudyExplosion::BeginPlay()
{
	Super::BeginPlay();
	
}

