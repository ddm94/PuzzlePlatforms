// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class PUZZLEPLATFORMS_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// By default C++ always expects to find an implementation for a function
	// If you do not want to be having an implementation, you need a pure virtual function
	// That means that it does not have an implementation and expects the class that inherits from it to implement that function
	// In our case - GameInstance
	virtual void Host() = 0; // = 0 This has an empty implementation
	virtual void Join(const FString &Address) = 0;
	virtual void LoadMainMenu() = 0;
};
