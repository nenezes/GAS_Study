// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.


#include "AbilitySystem/GAS_StudyAttributeSet.h"
#include "Net/UnrealNetwork.h"

UGAS_StudyAttributeSet::UGAS_StudyAttributeSet()
{
}

void UGAS_StudyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_StudyAttributeSet, Health, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_StudyAttributeSet, MaxHealth, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_StudyAttributeSet, Mana, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_StudyAttributeSet, MaxMana, COND_None, REPNOTIFY_OnChanged);
}

void UGAS_StudyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_StudyAttributeSet, Health, OldHealth);
}

void UGAS_StudyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_StudyAttributeSet, MaxHealth, OldMaxHealth);
}

void UGAS_StudyAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_StudyAttributeSet, Mana, OldMana);
}

void UGAS_StudyAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_StudyAttributeSet, MaxMana, OldMaxMana);
}
