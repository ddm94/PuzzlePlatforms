// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

void UMenuWidget::SetMenuInterface(IMenuInterface *_MenuInterface)
{
    MenuInterface = _MenuInterface;
}

void UMenuWidget::Setup()
{
    this->AddToViewport();

    UWorld *World = GetWorld();

    if (!ensure(World != nullptr))
        return;

    // Get a hold of the PlayerController
    APlayerController *PlayerController = World->GetFirstPlayerController();

    if (!ensure(PlayerController != nullptr))
        return;

    // Set the input mode
    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(this->TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    // Make the mouse cursor visible
    PlayerController->bShowMouseCursor = true;

    this->bIsFocusable = true;
}

void UMenuWidget::Teardown()
{
    this->RemoveFromViewport();

    UWorld *World = GetWorld();

    if (!ensure(World != nullptr))
        return;

    // Get a hold of the PlayerController
    APlayerController *PlayerController = World->GetFirstPlayerController();

    if (!ensure(PlayerController != nullptr))
        return;

    // Set the input mode
    FInputModeGameOnly InputModeData;
    PlayerController->SetInputMode(InputModeData);

    // Hide the cursor
    PlayerController->bShowMouseCursor = false;

    this->bIsFocusable = false;
}