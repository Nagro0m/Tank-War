#include "TankWarGame.h"
#include "AudioManager.h"
#include "Widget.h"
#include "Image.h"
#include "HUD.h"

using namespace UI;

TankWarGame::TankWarGame()
{
	label = nullptr;
	playersCount = 2;
	gameMode = new GameMode(playersCount);
}

TankWarGame::~TankWarGame()
{
	delete gameMode;
}

void TankWarGame::Start()
{
	level = Level();
	level.GenerateLevel();

	M_GAMEHUD.Initialize(2);
	gameMode->Initialize();

	Super::Start();
}

bool TankWarGame::Update()
{
	Super::Update();
	return IsOver();
}

void TankWarGame::Stop()
{
	Super::Stop();
}

void TankWarGame::GetDataFromSave()
{
	
}