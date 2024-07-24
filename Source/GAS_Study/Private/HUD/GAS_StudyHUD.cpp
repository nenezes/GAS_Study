// Copyright (c) 2024, Gabriel Menezes Concencio. All rights reserved.


#include "HUD/GAS_StudyHUD.h"

#include "Blueprint/UserWidget.h"

void AGAS_StudyHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UGAS_StudyUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
