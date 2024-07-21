// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.


#include "AbilitySystem/GAS_StudyAbilitySystemComponent.h"

void UGAS_StudyAbilitySystemComponent::AddCharacterAbility(const TSubclassOf<UGameplayAbility>& GameplayAbility,
                                                           const int32 AbilityLevel)
{
	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(GameplayAbility, AbilityLevel);

	GiveAbility(AbilitySpec);
}
