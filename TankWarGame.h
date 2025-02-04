#pragma once
#include "Game.h"
#include "MusicSample.h"
#include "Level.h"
#include "Label.h"
#include "Tank.h"
#include "TankCreation.h"
#include "CameraManager.h"

using namespace UI;

class TankWarGame : public Game
{
	MeshActor* background;
	MusicSample* music;
	Level level;
	Label* label;
	map<string, MeshActor*> uiAssets;
	Tank* player1Tank;
	Tank* player2Tank;
	CameraActor* cameraMainMenu;
	CameraActor* cameraPlayer1;
	CameraActor* cameraPlayer2;
	TankCreation* tankCreation;
	
public:
	TankWarGame();
	~TankWarGame();
	
public:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;



public:

	void MainMenu();
	void GenerateMainMenu();

	void GenerateSettingsMenu();

	MeshActor* CreateActors(const Vector2f& _size, const string& _texture, const Vector2f& _position,
		bool _useMiddleOrigin = true, float _rotation = 0.0f)
	{
		MeshActor* _actor = Level::SpawnActor(MeshActor(RectangleShapeData(_size, _texture)));

		if (_useMiddleOrigin)
		{
			_actor->SetOriginAtMiddle();
		}
		_actor->SetPosition(_position);
		if (_rotation != 0.0f)
		{
			_actor->Rotate(degrees(_rotation));
		}
		return _actor;
	}
};