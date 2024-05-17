// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
		return false;

	if (!ensure(Btn_Host != nullptr)) return false;
	Btn_Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	if (!ensure(Btn_ConfirmJoin != nullptr)) return false;
	Btn_ConfirmJoin->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);


	if (!ensure(Btn_Join != nullptr)) return false;
	Btn_Join->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	if (!ensure(Btn_Back != nullptr)) return false;
	Btn_Back->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(Btn_QuitGame != nullptr)) return false;
	Btn_QuitGame->OnClicked.AddDynamic(this, &UMainMenu::QuitPressed);

	

	return true;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr)
	{
		if (!ensure(IPAddressText != nullptr)) return;
		const FString& Address = IPAddressText->GetText().ToString();
		MenuInterface->Join(Address);
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::QuitPressed()
{
	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}

