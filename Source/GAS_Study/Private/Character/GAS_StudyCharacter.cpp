// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/GAS_StudyCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "AbilitySystem/GAS_StudyAbilitySystemComponent.h"
#include "AbilitySystem/GAS_StudyAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);


AGAS_StudyCharacter::AGAS_StudyCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	// Create an AbilitySystemComponent, enable replication on it and set its replication mode
	AbilitySystemComponent = CreateDefaultSubobject<UGAS_StudyAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Create an AttributeSet
	AttributeSet = CreateDefaultSubobject<UGAS_StudyAttributeSet>("AttributeSet");
}

FVector AGAS_StudyCharacter::GetHandSocketLocation()
{
	return GetMesh()->GetSocketLocation(HandSocketName);
}

void AGAS_StudyCharacter::InitializeClassDefaults()
{
	if (!HasAuthority())
	{
		return;
	}

	check(IsValid(AbilitySystemComponent));
	
	check(DefaultAttributesInitEffect);

	// Apply Default Attributes Gameplay Effect
	const FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributesInitEffect, 1.f, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

	// Grant abilities in list
	UGAS_StudyAbilitySystemComponent* GAS_StudyASC = CastChecked<UGAS_StudyAbilitySystemComponent>(AbilitySystemComponent);
	
	GAS_StudyASC->AddCharacterAbility(FireAbility, 1);
	
	GAS_StudyASC->AddCharacterAbility(AltFireAbility, 1);
}

void AGAS_StudyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGAS_StudyCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGAS_StudyCharacter::Look);

		// Fire
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AGAS_StudyCharacter::Fire);

		// AltFire
		EnhancedInputComponent->BindAction(AltFireAction, ETriggerEvent::Started, this, &AGAS_StudyCharacter::AltFire);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AGAS_StudyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	// Initialize Default Attributes on the Server, will automatically be replicated to the client
	InitializeClassDefaults();
}

void AGAS_StudyCharacter::OnAcknowledgePossession()
{
	// Init ability actor info for the Client
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AGAS_StudyCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AGAS_StudyCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGAS_StudyCharacter::TryActivateAbilityFromTag(FGameplayTag GameplayTag)
{
	TArray<FGameplayAbilitySpec> AbilitySpecs = AbilitySystemComponent->GetActivatableAbilities();

	// Activates ability that is not currently active and contains the exact Gameplay Tag 
	for (auto& AbilitySpec : AbilitySpecs)
	{
		if (AbilitySpec.Ability->AbilityTags.HasTagExact(GameplayTag) && !AbilitySpec.IsActive())
		{
			AbilitySystemComponent->TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void AGAS_StudyCharacter::Fire()
{
	check(IsValid(AbilitySystemComponent));

	TryActivateAbilityFromTag(FireAbilityTag);
}

void AGAS_StudyCharacter::AltFire()
{
	check(IsValid(AbilitySystemComponent));
	
	TryActivateAbilityFromTag(AltFireAbilityTag);
}
