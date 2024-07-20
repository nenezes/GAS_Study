// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Character/GAS_StudyCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GAS_StudyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAS_STUDY_API AGAS_StudyPlayerController : public APlayerController
{
	GENERATED_BODY()
	AGAS_StudyPlayerController();
	

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void AcknowledgePossession(APawn* P) override;
	
private:

	UPROPERTY()
	APawn* ControlledPawn;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> GAS_StudyContext;
};
