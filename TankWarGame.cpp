#include "TankWarGame.h"
#include "AudioManager.h"
#include "Widget.h"
#include "Image.h"
#include "HUD.h"

using namespace UI;

TankWarGame::TankWarGame()
{
	label = nullptr;
	//The file is located in x64/Debug/gameData
	GetDataFromSave("x64/Debug/gameData.txt");
	//Get the players count in int
	if (dataMap["playerCount"].size() != 0)
		playersCount = stof(dataMap["playerCount"]);
	else playersCount = 1;
	gameMode = new GameMode(playersCount);
}

TankWarGame::~TankWarGame()
{
	delete gameMode;
}

void TankWarGame::Start()
{
	level = Level();
	level.GenerateLevel();

	M_GAMEHUD.Initialize(2);
	gameMode->Initialize(dataMap);

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

void TankWarGame::GetDataFromSave(const string& _filePath)
{
	ifstream _file = ifstream(_filePath);
	if (!_file.is_open())
	{
		cout << "No files" << endl;
		return;
	}
	string _variable = "";
	string _value= "";

	string _line;
	while (getline(_file, _line))
	{
		SplitVariableValues(_line, _variable, _value);
		dataMap[_variable] = _value;
		_variable.clear();
		_value.clear();
	}
	_file.close();
}

void TankWarGame::SplitVariableValues(const string& _row, string& _variable, string& _value, const string& _separator)
{
	map <string, string> _mapOfVariablesAndValues;
	bool _isValue = false;
	for (u_int _index = 0; _index < size(_row); _index++)
	{
		if (_row[_index] == _separator)
		{
			_isValue = true;
			continue;
		}
		else if (_isValue)
		{
			_value += _row[_index];
		}
		else
		{
			_variable += _row[_index];
		}
	}
}
