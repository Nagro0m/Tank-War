#pragma once
#include "Tank.h"
#include "CameraManager.h"

class GameMode 
{
	Tank* player1Tank;
	Tank* player2Tank;

	CameraActor* cameraSolo;
	FloatRect cameraZoneSolo;

	CameraActor* cameraPlayer1;
	CameraActor* cameraPlayer2;
	FloatRect cameraZoneDuo;

	vector<Code> inputPlayer1;
	vector<Code> inputPlayer2;

	float playersCount;


public:
	GameMode(const float _playersCount = 1);

public:

	void Initialize();
	void InitializeSolo();
	void InitializeDuo();

};


