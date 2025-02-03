#include "GameMode.h"

GameMode::GameMode()
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

}

void GameMode::InitializeSolo()
{
	player1Tank = Level::SpawnActor(Tank(inputPlayer1, "Tank/Tank_1"));
	player1Tank->SetPosition(Vector2f(200.0f, 200.0f));

	FloatRect _rect = { Vector2f(100.0f , 100.0f), Vector2f(1820.0f, 980.0f) };
	cameraSolo = Camera::M_CAMERA.CreateCamera(CameraActor(Vector2f(), Vector2f(1920, 1080), "cameraSolo"));
	cameraSolo->SetTargetRect(_rect);
	cameraSolo->SetTarget(player1Tank);
	cameraSolo->Zoom(0.9);
	Camera::M_CAMERA.SetCurrent(cameraSolo);
}

void GameMode::InitializeDuo()
{
	player1Tank = Level::SpawnActor(Tank(inputPlayer2, "Tank/Tank_1"));
	player2Tank = Level::SpawnActor(Tank(inputPlayer2, "Tank/Tank_2"));

	cameraPlayer1 = Camera::M_CAMERA.CreateCamera(CameraActor(Vector2f(), Vector2f(1920 / 2, 1080), "TankCamera1"));
	cameraPlayer1->SetTarget(player1Tank);
	Camera::M_CAMERA.SetCurrent(cameraPlayer1);
	Camera::M_CAMERA.GetCurrent()->SetViewport({ Vector2f(0,0), Vector2f(0.5f, 1) });

	cameraPlayer2 = Camera::M_CAMERA.CreateCamera(CameraActor(Vector2f(), Vector2f(1920 / 2, 1080), "TankCamera2"));
	cameraPlayer2->SetTarget(player2Tank);
	Camera::M_CAMERA.SetCurrent(cameraPlayer2);
	Camera::M_CAMERA.GetCurrent()->SetViewport({ Vector2f(0.5f,0), Vector2f(0.5f, 1) });
}
