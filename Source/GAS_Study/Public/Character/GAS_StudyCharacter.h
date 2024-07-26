// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AttributeSet.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "GAS_StudyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AGAS_StudyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;
	
	/** AltFire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AltFireAction;

public:
	AGAS_StudyCharacter();

	/** Returns Ability System Component */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}

	/** Returns Attribute Set */
	UAttributeSet* GetAttributeSet() const
	{
		return AttributeSet;
	}

	/** Called when a controller possesses this character */
	virtual void PossessedBy(AController* NewController) override;

	/** Called on the client when a controller possesses this character */
	virtual void OnAcknowledgePossession();

	/** Returns hand socket location */
	FVector GetHandSocketLocation();
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
protected:

	/** Called for movement input **/
	void Move(const FInputActionValue& Value);

	/** Called for looking input **/
	void Look(const FInputActionValue& Value);
			
	/** Called for fire input **/
	void Fire();

	/** Called for alt fire input **/
	void AltFire();

	/** Adds mapping context and setup action bindings **/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Character's ability system component */
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	/** Character's attribute set */
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	/** Character's hand socket name */
	UPROPERTY(EditAnywhere, Category = "Sockets")
	FName HandSocketName;
	
	/** Gameplay effect that determines the character's starting attribute values */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttributesInitEffect;

	/** Applies DefaultAttributesInitEffect to initialize the character's attributes and grants DefaultAbilities' abilities */
	UFUNCTION(BlueprintCallable)
	void InitializeClassDefaults();

	/** Tries to active an ability that has a given tag */
	void TryActivateAbilityFromTag(FGameplayTag GameplayTag);

private:

	/** Character's default Fire ability */
	UPROPERTY(EditAnywhere, Category = "Gameplay Abilities")
	TSubclassOf<UGameplayAbility> FireAbility;

	/** Character's Fire ability Gameplay Tag*/
	UPROPERTY(EditAnywhere, Category = "Gameplay Abilities")
	FGameplayTag FireAbilityTag;

	/** Character's default AltFire ability */
	UPROPERTY(EditAnywhere, Category = "Gameplay Abilities")
	TSubclassOf<UGameplayAbility> AltFireAbility;

	/** Character's AltFire ability Gameplay Tag*/
	UPROPERTY(EditAnywhere, Category = "Gameplay Abilities")
	FGameplayTag AltFireAbilityTag;
};

