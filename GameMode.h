#pragma once
#include "Tank.h"
#include "CameraManager.h"

class GameMode
{
	Tank* player1Tank;
	Tank* player2Tank;

	CameraActor* cameraSolo;

	CameraActor* cameraPlayer1;
	CameraActor* cameraPlayer2;

	vector<Code> inputPlayer1;
	vector<Code> inputPlayer2;

public:
	GameMode();

public:

	void InitializeSolo();
	void InitializeDuo();

};


