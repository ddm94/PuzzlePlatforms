// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Constructor
AMovingPlatform::AMovingPlatform()
{
    // Enable ticking on this object
    PrimaryActorTick.bCanEverTick = true;

    // Set our component from static to movable
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        // Actor replication
        SetReplicates(true);
        SetReplicateMovement(true);
    }
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority()) // !HasAuthority == Not on server; Client
    {
        FVector Location = GetActorLocation();
        Location += FVector(Speed * DeltaTime, 0, 0);
        // Update actor location
        SetActorLocation(Location);
    }
}
