#pragma once
#include "Game.h"
#include "CameraManager.h"
#include "GameMode.h"
#include "GameHUD.h"

using namespace UI;
class MusicSample;

class TankWarMenu : public Game
{
	MeshActor* background;
	MusicSample* music;
	CameraActor* cameraMainMenu;
	map<string, MeshActor*> uiAssets;

public:
	TankWarMenu();
	~TankWarMenu();

public:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;

private:

	void MainMenu();
	void GenerateMainMenu();
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