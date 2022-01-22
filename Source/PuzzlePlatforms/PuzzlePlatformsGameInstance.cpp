// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer)
{
    // We get a hold of our MainMenu Blueprint class
    ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));

    if (!ensure(MenuBPClass.Class != nullptr))
        return;

    MenuClass = MenuBPClass.Class;

    ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));

    if (!ensure(InGameMenuBPClass.Class != nullptr))
        return;

    InGameMenuClass = InGameMenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
    UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());

    UEngine *Engine = GetEngine();

    if (!ensure(Engine != nullptr))
        return;

    // We bind our own function to handle network failure to the Engine's OnNetworkFailure
    Engine->OnNetworkFailure().AddUObject(this, &UPuzzlePlatformsGameInstance::NetworkError);
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
    if (!ensure(MenuClass != nullptr))
        return;

    Menu = CreateWidget<UMainMenu>(this, MenuClass);

    if (!ensure(Menu != nullptr))
        return;

    Menu->Setup();
    Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::InGameLoadMenu()
{
    if (!ensure(InGameMenuClass != nullptr))
        return;

    UMenuWidget *GameInstanceMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);

    if (!ensure(GameInstanceMenu != nullptr))
        return;

    GameInstanceMenu->Setup();
    GameInstanceMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host()
{
    if (Menu != nullptr)
    {
        Menu->Teardown();
    }

    if (!ensure(GEngine != nullptr))
        return;

    GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

    // Server Travelling
    UWorld *World = GetWorld();

    if (!ensure(World != nullptr))
        return;

    // Travel from Lobby to the specified map
    // Argument: listen = Specify server as a listen server
    World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString &Address)
{
    if (Menu != nullptr)
    {
        Menu->Teardown();
    }

    if (!ensure(GEngine != nullptr))
        return;

    GEngine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining: %s"), *Address));

    // Client Travelling
    // Get hold of the player controller
    APlayerController *PlayerController = GetFirstLocalPlayerController();

    if (!ensure(PlayerController != nullptr))
        return;

    PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
    APlayerController *PlayerController = GetFirstLocalPlayerController();

    if (!ensure(PlayerController != nullptr))
        return;

    PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}

// If the host leaves the server, prevents all connected game clients from crashing.
// Instead, they will simply go to the main menu.
void UPuzzlePlatformsGameInstance::NetworkError(UWorld *World, UNetDriver *NetDriver, ENetworkFailure::Type FailureType, const FString &ErrorString)
{
    LoadMainMenu();
}