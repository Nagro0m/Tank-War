#pragma once
#include "HUD.h"
#include "Image.h"

using namespace UI;

class GameHUD : public HUD
{
	UI::Image* separation;
	vector<UI::Image*> lifeBars;
	int playersCount;

public:
	GameHUD(const int _playersCount = 1);
	~GameHUD();

public:
	void Initialize();

	UI::Image* CreateLifeBar(const string& _name, const string& _texture, const Vector2f& _position);

};