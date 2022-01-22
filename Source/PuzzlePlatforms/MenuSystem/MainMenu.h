// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

/**
 *
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton *HostButton; // Forward declaration

	UPROPERTY(meta = (BindWidget))
	class UButton *JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *JoinGameButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher *MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget *JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget *MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *IPAddressField;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void BackToMenu();

	UFUNCTION()
	void QuitGame();
};
