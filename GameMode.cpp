#include "GameMode.h"
#include "Level.h"

GameMode::GameMode(const string& _name) : Actor(_name)
{
	controllerRef = PlayerController();
	controller = nullptr;
	hudRef = HUD();
	hud = nullptr;
}

GameMode::GameMode(const GameMode& _other) : Actor(_other)
{
	controllerRef = _other.controllerRef;
	controller = nullptr;
	hudRef = _other.hudRef;
	hud = nullptr;
}


void GameMode::Construct()
{
	Super::Construct();

	controller = GetPlayerController();
	hud = GetHUD();
}

PlayerController* GameMode::GetPlayerController()
{
	if (!controller)
	{
		controller = level->SpawnActor<PlayerController>(controllerRef);
	}

	return controller;
}

UI::HUD* GameMode::GetHUD()
{
	if (!hud)
	{
		hud = level->SpawnActor<HUD>(hudRef);
	}

	return hud;
}