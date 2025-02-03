#pragma once
#include "Game.h"
#include "MeshActor.h"
#include "MusicSample.h"
#include "Level.h"
#include "Label.h"
#include "CameraManager.h"
#include "GameMode.h"

using namespace UI;

class TankWarGame : public Game
{
	MeshActor* background;
	MusicSample* music;
	Level level;
	Label* label;
	map<string, MeshActor*> uiAssets;
	CameraActor* cameraMainMenu;
	GameMode* gameMode;


	
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