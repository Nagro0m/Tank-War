#include "TankWarGame.h"
#include "AudioManager.h"
#include "Widget.h"
#include "Image.h"
#include "HUD.h"


using namespace UI;

TankWarGame::TankWarGame()
{
	background = nullptr;
	music = nullptr;
	label = nullptr;
	cameraMainMenu = nullptr;
	playersCount = 2;
	gameMode = new GameMode(playersCount);
	gameHUD = new GameHUD(playersCount);

}

TankWarGame::~TankWarGame()
{
	delete gameMode;
	delete gameHUD;
	delete tankCreation;
}


void TankWarGame::Start()
{
	//level = Level();
	//level.GenerateLevel();
	////MainMenu();

	gameMode->Initialize();
	gameHUD->Initialize();

	//vector<Code> _tank1 =
	//{
	//	Code::A,
	//	Code::D,
	//	Code::W,
	//	Code::S,
	//};
	//vector<Code> _tank2 =
	//{
	//	Code::Left,
	//	Code::Right,
	//	Code::Up ,
	//	Code::Down,
	//};

	//player1Tank = Level::SpawnActor(Tank(_tank1, "Tank/Tank_1"));
	//player2Tank = Level::SpawnActor(Tank(_tank2, "Tank/Tank_2"));

	//cameraPlayer1 = Camera::M_CAMERA.CreateCamera(CameraActor(Vector2f(), Vector2f(1920 / 2, 1080), "TankCamera1"));
	//cameraPlayer1->SetTarget(player1Tank);
	//Camera::M_CAMERA.SetCurrent(cameraPlayer1);
	//Camera::M_CAMERA.GetCurrent()->SetViewport({Vector2f(0,0), Vector2f(0.5f, 1)});

	//cameraPlayer2 = Camera::M_CAMERA.CreateCamera(CameraActor(Vector2f(), Vector2f(1920 / 2, 1080), "TankCamera2"));
	//cameraPlayer2->SetTarget(player2Tank);
	//Camera::M_CAMERA.SetCurrent(cameraPlayer2);
	//Camera::M_CAMERA.GetCurrent()->SetViewport({ Vector2f(0.5f,0), Vector2f(0.5f, 1) });
	//player1Tank->SetPosition(Vector2f(300, 300));
	//MeshActor* _bar = CreateActors(Vector2f(100.0f, 0), "Menu/Separation", Vector2f(1920 / 2  , 1080), false, 0.0f);
	
	tankCreation = new TankCreation();
	tankCreation->Start();

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
	// Configurer la caméra et le menu
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
