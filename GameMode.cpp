#include "GameMode.h"
#include "TankCreation.h"


GameMode::GameMode(const float _playersCount)
{
	player1Tank = nullptr;
	player2Tank = nullptr;

	cameraSolo = nullptr;
	cameraPlayer1 = nullptr;
	cameraPlayer2 = nullptr;


	inputPlayer1 =
	{
		KeyType::Q,
		KeyType::D,
		KeyType::Z,
		KeyType::S,
		KeyType::A
	};

	inputPlayer2 =
	{
		KeyType::Left_Arrow,
		KeyType::Right_Arrow,
		KeyType::Up_Arrow,
		KeyType::Down_Arrow,
		KeyType::Enter
	};

	cameraZoneSolo = { Vector2f(500.0f , 200.0f), Vector2f(3340.0f, 1960.0f) };
	cameraZoneDuo = { Vector2f(200.0f , 250.0f), Vector2f(3540.0f, 1820.0f) };

	playersCount = _playersCount;

}


void GameMode::Initialize(const map <string, string>& _dataMap)
{
	dataMap = _dataMap;
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
	//player1Tank = Level::SpawnActor(Tank(inputPlayer1, "Tank/Tank_1", "Player1"));
	player1Tank->SetPosition(Vector2f(500.0f, 500.0f));

	cameraSolo = Camera::M_CAMERA.CreateCamera(CameraActor(Vector2f(), Vector2f(1920, 1080), "cameraSolo"));
	cameraSolo->SetTargetRect(cameraZoneSolo);
	cameraSolo->SetTarget(player1Tank);
	Camera::M_CAMERA.SetCurrent(cameraSolo);
}

void GameMode::InitializeDuo()
{
	const string& _trackAsset1 = "Tank/Tracks/Track_" + GetValueFromVariable("track", 0);
	player1Tank = Level::SpawnActor(Tank(inputPlayer1, _trackAsset1, "Player1"));
	player1Tank->SetHull("Hulls_1/Hull_" + GetValueFromVariable("hull", 0));
	player1Tank->SetWeapon("Weapons_1/Gun_" + GetValueFromVariable("weapon", 0));
	player1Tank->SetPosition(Vector2f(300.0f, 300.0f));

	const string& _trackAsset2 = "Tank/Tracks/Track_" + GetValueFromVariable("track", 1);
	player2Tank = Level::SpawnActor(Tank(inputPlayer2, _trackAsset2, "Player2"));
	player2Tank->SetHull("Hulls_2/Hull_" + GetValueFromVariable("hull", 1));
	player2Tank->SetWeapon("Weapons_2/Gun_" + GetValueFromVariable("weapon", 1));
	player2Tank->SetPosition(Vector2f(600.0f, 600.0f));
	

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

}

string GameMode::GetValueFromVariable(const string& _variable, int _valueId)
{
	string _values = dataMap[_variable];
	string _valueToReturn;
	const u_int _size = static_cast<u_int>(size(_values));
	int _valueNumber = 0;
	for (u_int _index = 0; _index < _size; _index++)
	{
		if (_values[_index] == '-')
		{
			++_valueNumber;
			continue;
		}
		if (_valueNumber == _valueId) _valueToReturn += _values[_index];
	}
	return _valueToReturn;
}
