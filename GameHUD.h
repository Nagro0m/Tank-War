#pragma once
#include "HUD.h"
#include "Image.h"
#include "Singleton.h"

using namespace UI;

class GameHUD : public Singleton<GameHUD>
{
	UI::Image* separation;
	map<string , UI::Image*> lifeBars;
	int playersCount;

public:
	GameHUD();
	~GameHUD();

public:
	void Initialize(const int _playersCount = 1);

	UI::Image* CreateLifeBar(const string& _name, const string& _texture, const Vector2f& _position);
	void ChangeLifeBarWithLife(const string& _name, const float _life);

	void SpawnLoadAnimation();


};