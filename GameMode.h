#pragma once
#include "Tank.h"
#include "CameraManager.h"
#include "InputManager.h"

using namespace Input;
class GameMode
{
	map<string, string> dataMap;
	Tank* player1Tank;
	Tank* player2Tank;

	CameraActor* cameraSolo;
	FloatRect cameraZoneSolo;

	CameraActor* cameraPlayer1;
	CameraActor* cameraPlayer2;
	FloatRect cameraZoneDuo;

	vector<KeyType> inputPlayer1;
	vector<KeyType> inputPlayer2;

	float playersCount;


public:
	GameMode(const float _playersCount = 1);

public:

	void Initialize(const map <string, string>& _dataMap);
	void InitializeSolo();
	void InitializeDuo();

private:
	string GetValueFromVariable(const string& _variable, int _valueId);
};