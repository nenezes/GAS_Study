// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.


#include "Player/GAS_StudyPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AGAS_StudyPlayerController::AGAS_StudyPlayerController()
{
	bReplicates = true;
}

void AGAS_StudyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(GAS_StudyContext);
	
	ControlledPawn = GetPawn<APawn>();
}

void AGAS_StudyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
}

void AGAS_StudyPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	if (GetPawn<APawn>()->IsLocallyControlled())
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		
		check(Subsystem);
		
		Subsystem->AddMappingContext(GAS_StudyContext, 0);
	}

	AGAS_StudyCharacter* GAS_StudyCharacter = Cast<AGAS_StudyCharacter>(P);
	GAS_StudyCharacter->OnAcknowledgePossession();
}
