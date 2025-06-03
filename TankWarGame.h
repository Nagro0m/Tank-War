#pragma once
#include "Game.h"
#include "MusicSample.h"
#include "Level.h"
#include "Label.h"
#include "Tank.h"
#include "TankCreation.h"
#include "CameraManager.h"
#include "GameMode.h"
#include "GameHUD.h"

using namespace UI;

class TankWarGame : public Game
{

	Level level;
	Label* label;
	GameMode* gameMode;
	float playersCount;
	vector<string> datas;
	vector<Tank*> tanks;
	map <string, string> dataMap;
	//TankCreation* tankCreation;
	int winner;
	string saveFile = "x64/Debug/gameData.txt";
public:
	void SetWinner(const int _winner) { winner = _winner; }
	void AddTank(Tank* _tankToAdd) { tanks.push_back(_tankToAdd); }

public:
	TankWarGame();
	~TankWarGame();
	
public:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;

private:
	
	void GetDataFromSave(const string& _filePath);
	void SaveData(const string& _filePath);
	void SplitVariableValues(const string& _row, string& _variable, string& _value, const string& _separator = ":");
};