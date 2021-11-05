// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
}

void UPuzzlePlatformsGameInstance::Init()
{
    UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}

void UPuzzlePlatformsGameInstance::Host()
{
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