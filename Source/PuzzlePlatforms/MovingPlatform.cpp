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

    GlobalStartLocation = GetActorLocation();
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority()) // !HasAuthority == Not on server; Client
    {
        FVector Location = GetActorLocation();
        float JourneyLength =  (GlobalTargetLocation - GlobalStartLocation).Size();
        float JourneyTravelled = (Location - GlobalStartLocation).Size();

        if (JourneyTravelled >= JourneyLength) 
        {
            FVector Swap = GlobalStartLocation;

            GlobalStartLocation = GlobalTargetLocation;
            GlobalTargetLocation = Swap;
        }
        
        // Convert TargetLocation which is a local FVector into a global one.
        // FVector GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

        FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

        //Location += FVector(Speed * DeltaTime, 0, 0);

        Location += Speed * DeltaTime * Direction;

        // Update actor location
        SetActorLocation(Location);
    }
}
