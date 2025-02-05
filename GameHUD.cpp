#include "GameHUD.h"

GameHUD::GameHUD(const int _playersCount)
{
	separation = nullptr;
	playersCount = _playersCount;
}

GameHUD::~GameHUD()
{
}

void GameHUD::Initialize()
{
	Vector2f lifeSize = Vector2f(375, 57.5);

	vector<Vector2f> _positions = 
	{
		Vector2f(50, 20),
		Vector2f(1920 - lifeSize.x - 50, 20),
	};
	vector<string> _textures =
	{ 
		"Menu/Life",
		"Menu/LifeGreen" 
	};

	for (int _index = 0; _index < playersCount; ++_index)
	{
		lifeBars["Player" + to_string(_index +1)] = CreateLifeBar("LifeBar" + to_string(_index + 1), _textures[_index], _positions[_index]);
	}

	if (playersCount > 1)
	{
		separation = M_HUD.CreateWidget<UI::Image>("Separation",RectangleShapeData(Vector2f(10, 1080),"Menu/Black"),Screen);
		separation->SetPosition(Vector2f(955, 0));
		M_HUD.AddToViewport(separation);
	}
}

UI::Image* GameHUD::CreateLifeBar(const string& _name, const string& _texture, const Vector2f& _position)
{
	UI::Image* _lifeBar = M_HUD.CreateWidget<UI::Image>(_name, RectangleShapeData(Vector2f(375, 57.5), _texture, PNG, 
		false, { Vector2i(), Vector2i(500, 71) }),Screen);

	_lifeBar->SetPosition(_position);
	M_HUD.AddToViewport(_lifeBar);

	return _lifeBar;
}

void GameHUD::ChangeLifeBarWithLife(const string& _name, const float _life)
{
	
}


