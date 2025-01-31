#include "TankWarGame.h"
#include "AudioManager.h"

TankWarGame::TankWarGame()
{
	background = nullptr;
	music = nullptr;
	label = nullptr;
	player1Tank = nullptr;
	player2Tank = nullptr;
	cameraMainMenu = nullptr;
}

TankWarGame::~TankWarGame()
{
}

void TankWarGame::Start()
{
	level = Level();
	level.GenerateLevel();
	//MainMenu();
	player1Tank = Level::SpawnActor(Tank("Tank/Tank_1"));
	player2Tank = Level::SpawnActor(Tank("Tank/Tank_2"));

	cameraMainMenu = Camera::M_CAMERA.CreateCamera(CameraActor(Vector2f(), Vector2f(640, 360), "TankCamera"));
	cameraMainMenu->SetTarget(player1Tank);
	Camera::M_CAMERA.SetCurrent(cameraMainMenu);

	player1Tank->SetPosition(Vector2f(150, 150));
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

void TankWarGame::MainMenu()
{
	// Configurer la cam�ra et le menu
	GenerateMainMenu();

	cameraMainMenu = Camera::M_CAMERA.CreateCamera(CameraActor(Vector2f(), Vector2f(2304, 1296), "TankCamera"));
	cameraMainMenu->SetTarget(uiAssets["Menu/Middle"]);
}

void TankWarGame::GenerateMainMenu()
{
	Vector2f _basePosition = Vector2f(-2500.0f, -1500.0f);

	background = CreateActors(Vector2f(2304, 1296), "Menu/Background/MenuBackground", (Vector2f(960, 600)) + Vector2f(-2500.0f, -1500.0f));
	music = M_AUDIO.PlaySample<MusicSample>("BackgroundMusic");

	vector<tuple<Vector2f, string, Vector2f, bool, float>> _assets =
	{
		{Vector2f(1000, 350), "Menu/TitleWithTank", Vector2f(960, 154), true, 0.0f},
		{Vector2f(1, 1), "Menu/Middle", Vector2f(960, 600), true, 0.0f},
		{Vector2f(500, 630), "Menu/SelectMenu", Vector2f(960, 650), true, 0.0f},
		{Vector2f(300, 100), "Menu/Button/ButtonSolo", Vector2f(960, 460), true, 0.0f},
		{Vector2f(300, 100), "Menu/Button/ButtonDuo", Vector2f(960, 580), true, 0.0f},
		{Vector2f(300, 100), "Menu/Button/ButtonSettings", Vector2f(960, 700), true, 0.0f},
		{Vector2f(300, 100), "Menu/Button/ButtonExit", Vector2f(960, 820), true, 0.0f},
	};

	for (const auto [_size, _texture, _position, _useMiddleOrigin, _rotation] : _assets)
	{
		Vector2f _adjustedPosition = _basePosition + _position;
		uiAssets[_texture] = CreateActors(_size, _texture, _adjustedPosition, _useMiddleOrigin, _rotation);
	}

}
