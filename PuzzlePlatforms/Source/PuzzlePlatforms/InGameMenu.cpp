// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"

#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(Btn_BacktoGame != nullptr)) return false;
	Btn_BacktoGame->OnClicked.AddDynamic(this, &UInGameMenu::BacktoGame);

	if (!ensure(Btn_QuitThisGame != nullptr)) return false;
	Btn_QuitThisGame->OnClicked.AddDynamic(this, &UInGameMenu::QuitThisGame);

	return true;
}

void UInGameMenu::BacktoGame()
{
	TearDown();
}

void UInGameMenu::QuitThisGame()
{
	if (MenuInterface != nullptr)
	{
		TearDown();
		MenuInterface->LoadMainMenu();
	}
}
