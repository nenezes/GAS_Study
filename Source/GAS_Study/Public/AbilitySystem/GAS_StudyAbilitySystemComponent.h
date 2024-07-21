// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GAS_StudyAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAS_STUDY_API UGAS_StudyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AddCharacterAbility(const TSubclassOf<UGameplayAbility>& GameplayAbility, int32 AbilityLevel);
};
