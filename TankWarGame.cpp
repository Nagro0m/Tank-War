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
	saveFile = "gameData.txt";
	GetDataFromSave(saveFile);
	//Get the players count in int
	if (dataMap["playerCount"].size() != 0)
		playersCount = stof(dataMap["playerCount"]);
	else playersCount = 1;
	gameMode = new GameMode(playersCount);
}

TankWarGame::~TankWarGame()
{
	delete label;
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
	for (Tank* _tank : tanks)
	{
		_tank->StopTank();
	}
	M_GAMEHUD.DeInitialize();
	SaveData(saveFile);
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

void TankWarGame::SaveData(const string& _filePath)
{
	ifstream inFile(_filePath);
	vector<string> lines;
	bool found = false;

	// Lire tout le fichier ligne par ligne
	string line;
	while (getline(inFile, line))
	{
		if (line.find("winner:") == 0)
		{
			found = true;
			int count = 0;

			// Extraire le nombre après "winner:"
			istringstream iss(line.substr(7)); // ignore "winner:"
			iss >> count;
			++count;

			line = "winner:" + to_string(count);
		}

		lines.push_back(line);
	}
	inFile.close();

	if (!found)
	{
		lines.push_back("winner:-1");
	}

	// Réécriture du fichier avec les lignes mises à jour
	ofstream outFile(_filePath);
	for (const string& updatedLine : lines)
	{
		outFile << updatedLine << '\n';
	}
	outFile.close();
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
