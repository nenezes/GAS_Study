// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GAS_StudyExplosion.generated.h"

UCLASS()
class GAS_STUDY_API AGAS_StudyExplosion : public AActor
{
	GENERATED_BODY()

public:
	AGAS_StudyExplosion();

protected:
	virtual void BeginPlay() override;

};
