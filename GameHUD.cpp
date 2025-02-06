#include "GameHUD.h"
#include "Level.h"
#include "LoadAnimation.h"

GameHUD::GameHUD()
{
	separation = nullptr;
}

GameHUD::~GameHUD()
{
}

void GameHUD::Initialize(const int _playersCount)
{
	playersCount = _playersCount;


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
		false, { Vector2i(), Vector2i(500, 427) }),Screen);

	_lifeBar->SetPosition(_position);
	M_TEXTURE.SetTextureRect(_lifeBar->GetShape(), Vector2i(), Vector2i(500, 71));
	M_HUD.AddToViewport(_lifeBar);

	

	return _lifeBar;
}

void GameHUD::ChangeLifeBarWithLife(const string& _name, const float _life)
{
	if (!lifeBars[_name])
	{
		LOG(Error, "no life bar is called : " + _name);
		return;
	}
	
	M_TEXTURE.SetTextureRect(lifeBars[_name]->GetShape(), Vector2i(0, (5 - (_life / 20)) * 73), Vector2i(500, 62));
	
}

void GameHUD::SpawnLoadAnimation()
{

	LoadAnimation* _load = Level::SpawnActor(LoadAnimation(RectangleShapeData(Vector2f(100.0f, 100.0f), "Effects/Load4")));
	_load->SetOriginAtMiddle();
	_load->SetPosition(Vector2f(200, 200));
}



