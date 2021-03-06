// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
    bool Success = Super::Initialize();

    if (!Success)
        return false;

    if (!ensure(HostButton != nullptr))
        return false;

    HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

    if (!ensure(JoinGameButton != nullptr))
        return false;

    JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

    if (!ensure(JoinButton != nullptr))
        return false;

    JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

    if (!ensure(CancelButton != nullptr))
        return false;

    QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

    if (!ensure(QuitButton != nullptr))
        return false;

    CancelButton->OnClicked.AddDynamic(this, &UMainMenu::BackToMenu);

    return true;
}

void UMainMenu::HostServer()
{
    UE_LOG(LogTemp, Warning, TEXT("I'm gonna host a server!"));

    if (MenuInterface != nullptr)
    {
        MenuInterface->Host();
    }
}

void UMainMenu::JoinServer()
{
    UE_LOG(LogTemp, Warning, TEXT("I'm joining a server!"));

    if (MenuInterface != nullptr)
    {
        if (!ensure(IPAddressField != nullptr))
            return;

        const FString &Address = IPAddressField->GetText().ToString();

        MenuInterface->Join(Address);
    }
}

void UMainMenu::OpenJoinMenu()
{
    if (!ensure(MenuSwitcher != nullptr))
        return;

    if (!ensure(JoinMenu != nullptr))
        return;

    MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::BackToMenu()
{
    if (!ensure(MenuSwitcher != nullptr))
        return;

    if (!ensure(MainMenu != nullptr))
        return;

    MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::QuitGame()
{
    UWorld *World = GetWorld();

    if (!ensure(World != nullptr))
        return;

    APlayerController *PlayerController = World->GetFirstPlayerController();

    if (!ensure(PlayerController != nullptr))
        return;

    PlayerController->ConsoleCommand("quit");
}