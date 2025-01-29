#include "TankWarGame.h"
#include "AudioManager.h"

TankWarGame::TankWarGame()
{
}

TankWarGame::~TankWarGame()
{
}

void TankWarGame::Start()
{
	level = Level();
	level.GenerateLevel();
	TankCreation _tank = TankCreation();
	_tank.CreateTank();
	Super::Start();
	//GenerateMainMenu();
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

void TankWarGame::GenerateMainMenu()
{
	Vector2f _windowSize = CAST(Vector2f, window.getSize());
	background = CreateActors(_windowSize, "Menu/Background/MenuBackground", _windowSize / 2.0f);
	//music = M_AUDIO.PlaySample<MusicSample>("BackgroundMusic");

	vector<tuple<Vector2f, string, Vector2f, bool, float>> _assets =
	{
		{Vector2f(1000, 350), "Menu/TitleWithTank", {_windowSize.x / 2.0f, _windowSize.y / 7.0f}, true, 0.0f},
		{Vector2f(500, 630), "Menu/SelectMenu", {_windowSize.x / 2.0f, 650}, true, 0.0f},
		{Vector2f(300, 100), "Menu/Button/ButtonSolo", Vector2f(_windowSize.x / 2.0f, 460.0f), true, 0.0f},
		{Vector2f(300, 100), "Menu/Button/ButtonDuo", Vector2f(_windowSize.x / 2.0f, 580), true, 0.0f},
		{Vector2f(300, 100), "Menu/Button/ButtonSettings", Vector2f(_windowSize.x / 2.0f, 700), true, 0.0f},
		{Vector2f(300, 100), "Menu/Button/ButtonExit", Vector2f(_windowSize.x / 2.0f, 820.0f), true, 0.0f},
	};

	for (const auto [_size, _texture, _position, _useMiddleOrigin, _rotation] : _assets)
	{
		uiAssets.push_back(CreateActors(_size, _texture, _position, _useMiddleOrigin, _rotation));
	}
}
