// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"

#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
    bool Success = Super::Initialize();

    if (!Success)
        return false;

    if (!ensure(CancelButton != nullptr))
        return false;

    CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::Cancel);

    if (!ensure(QuitButton != nullptr))
        return false;

    QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitToMenu);

    return true;
}

// We call the Teardown function on the parent class which does exactly what we need for this cancel button
// Without needing to write a new function
void UInGameMenu::Cancel()
{
    Teardown();
}

void UInGameMenu::QuitToMenu()
{
    if (MenuInterface != nullptr)
    {
        Teardown();
        MenuInterface->LoadMainMenu();
    }
}