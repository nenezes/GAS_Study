// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD/GAS_StudyUserWidget.h"
#include "GAS_StudyHUD.generated.h"



/**
 * 
 */
UCLASS()
class GAS_STUDY_API AGAS_StudyHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
private:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGAS_StudyUserWidget> OverlayWidgetClass;
};
