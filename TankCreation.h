#pragma once
#include "Level.h"
#include "Hull.h"
#include "Weapon.h"
#include "Track.h"
#include "Label.h"

class Tank;

class TankCreation
{
	Vector2f tankMenuPosition;
	int currentStep;
	int trackIndex;
	int hullIndex;
	int weaponIndex;
	vector<Hull> hulls;
	vector<Weapon> weapons;
	vector<Track> tracks;
	MeshActor* currentActor;
	vector<MeshActor*> tankMenu;
	UI::Label* menuLabel;
public:
	TankCreation(const Vector2f& _tankMenuPosition = Vector2f(-1000.0f, -1000.0f));

public:
	void Start();

private:
	vector<Track> GetTracks();
	vector<Weapon> GetWeapons();
	vector<Hull> GetHulls();
	void GenerateTankCreationMenu();
	void PreviousOption();
	void NextOption();
	void SpawnCurrentSelection();
	void RemoveCurrentSelection();
	void ConfirmSelection();
	void FinalizeTank();

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

