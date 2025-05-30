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
	map <string, string> dataMap;
	//TankCreation* tankCreation;

	
public:
	TankWarGame();
	~TankWarGame();
	
public:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;

private:
	
	void GetDataFromSave(const string& _filePath);
	void SplitVariableValues(const string& _row, string& _variable, string& _value, const string& _separator = ":");
};