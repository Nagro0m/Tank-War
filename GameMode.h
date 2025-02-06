#pragma once
#include "Tank.h"
#include "CameraManager.h"
#include "InputManager.h"

using namespace Input;
class GameMode 
{
	Tank* player1Tank;
	Tank* player2Tank;

	CameraActor* cameraSolo;
	FloatRect cameraZoneSolo;

	CameraActor* cameraPlayer1;
	CameraActor* cameraPlayer2;
	FloatRect cameraZoneDuo;

	vector<Key> inputPlayer1;
	vector<Key> inputPlayer2;

	float playersCount;


public:
	GameMode(const float _playersCount = 1);

public:

	void Initialize();
	void InitializeSolo();
	void InitializeDuo();

};


