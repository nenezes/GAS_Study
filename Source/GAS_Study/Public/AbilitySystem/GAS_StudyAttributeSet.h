// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAS_StudyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class GAS_STUDY_API UGAS_StudyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UGAS_StudyAttributeSet();

	//Set the conditions in which each attribute is replicated
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/*
	* Attribute declarations
	*/
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGAS_StudyAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGAS_StudyAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UGAS_StudyAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UGAS_StudyAttributeSet, MaxMana);

	/*
	* On replicated attribute callback functions.
	*/
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
};
