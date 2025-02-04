#include "GameMode.h"

GameMode::GameMode(const float _playersCount)
{
	player1Tank = nullptr;
	player2Tank = nullptr;

	cameraSolo = nullptr;
	cameraPlayer1 = nullptr;
	cameraPlayer2 = nullptr;

	inputPlayer1 =
	{
		Code::A,
		Code::D,
		Code::W,
		Code::S,
	};
	inputPlayer2 =
	{
		Code::Left,
		Code::Right,
		Code::Up ,
		Code::Down,
	};

	cameraZoneSolo = { Vector2f(500.0f , 200.0f), Vector2f(3340.0f, 1960.0f) };
	cameraZoneDuo = { Vector2f(200.0f , 250.0f), Vector2f(3540.0f, 1820.0f) };

	playersCount = _playersCount;

}


void GameMode::Initialize()
{
	if (playersCount == 2)
	{
		InitializeDuo();
	}
	else
	{
		InitializeSolo();
	}
}

void GameMode::InitializeSolo()
{
	player1Tank = Level::SpawnActor(Tank(inputPlayer1, "Tank/Tank_1"));
	player1Tank->SetPosition(Vector2f(500.0f, 500.0f));

	cameraSolo = Camera::M_CAMERA.CreateCamera(CameraActor(Vector2f(), Vector2f(1920, 1080), "cameraSolo"));
	cameraSolo->SetTargetRect(cameraZoneSolo);
	cameraSolo->SetTarget(player1Tank);
	Camera::M_CAMERA.SetCurrent(cameraSolo);
}

void GameMode::InitializeDuo()
{
	player1Tank = Level::SpawnActor(Tank(inputPlayer1, "Tank/Tank_1"));
	player1Tank->SetPosition(Vector2f(300.0f, 300.0f));
	player2Tank = Level::SpawnActor(Tank(inputPlayer2, "Tank/Tank_2"));
	player2Tank->SetPosition(Vector2f(3440.0f, 1760.0f));

	

	cameraPlayer1 = Camera::M_CAMERA.CreateCamera(CameraActor(Vector2f(), Vector2f(1920 / 2, 1080), "TankCamera1"));
	cameraPlayer1->SetTargetRect(cameraZoneDuo);
	cameraPlayer1->SetTarget(player1Tank);
	Camera::M_CAMERA.SetCurrent(cameraPlayer1);
	Camera::M_CAMERA.GetCurrent()->SetViewport({ Vector2f(), Vector2f(0.5f, 1.0f) });

	cameraPlayer2 = Camera::M_CAMERA.CreateCamera(CameraActor(Vector2f(), Vector2f(1920 / 2, 1080), "TankCamera2"));
	cameraPlayer2->SetTargetRect(cameraZoneDuo);
	cameraPlayer2->SetTarget(player2Tank);
	Camera::M_CAMERA.SetCurrent(cameraPlayer2);
	Camera::M_CAMERA.GetCurrent()->SetViewport({ Vector2f(0.5,0), Vector2f(0.5, 1) });


	//UI::Image* _image = M_HUD.CreateWidget<UI::Image>("TEST", RectangleShapeData(Vector2f(10, 1080), "Menu/Black"), Screen);
	//_image->SetPosition(Vector2f(955, 0));
	//M_HUD.AddToViewport(_image);

	//Vector2f _lifeSize = Vector2f(375, 57.5);
	//UI::Image* _life = M_HUD.CreateWidget<UI::Image>("TEST", RectangleShapeData(_lifeSize, "Menu/Life",
	//	PNG, false, { Vector2i(), Vector2i(500, 71) }), Screen);
	//_life->SetPosition(Vector2f(50, 20));
	//M_HUD.AddToViewport(_life);

	//UI::Image* _life2 = M_HUD.CreateWidget<UI::Image>("TEST", RectangleShapeData(_lifeSize, "Menu/LifeGreen",
	//	PNG, false, { Vector2i(), Vector2i(500, 71) }), Screen);
	//_life2->SetPosition(Vector2f(1920 - _lifeSize.x - 50, 20));
	//M_HUD.AddToViewport(_life2);


}
