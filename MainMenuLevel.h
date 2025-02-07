#pragma once
#include "Level.h"
#include "MeshActor.h"
#include "MusicSample.h"
#include "FollowCamera.h"

class MainMenuLevel : public Level
{
	MeshActor* background;
	MusicSample* music;
	map<string, MeshActor*> uiAssets;
	FollowCamera* cameraMainMenu;

public:
	MainMenuLevel();

public:

	void GenerateMainMenu();
	

public:

	virtual void Load();
	virtual void Unload();

protected:
	virtual void InitLevel();


	// MAGNIFIQUE / CHOUETTTTTTTTTE / SUBLIME / EXCELLENT / WOW T'AS MIS DU TEMPS 
	MeshActor* CreateActors(const Vector2f& _size, const string& _texture, const Vector2f& _position,
		bool _useMiddleOrigin = true, float _rotation = 0.0f)
	{
		MeshActor* _actor = SpawnActor<MeshActor>(RectangleShapeData(_size, _texture));

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

