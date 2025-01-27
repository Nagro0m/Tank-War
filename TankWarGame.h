#pragma once
#include "Game.h"
#include "MeshActor.h"
#include "MusicSample.h"

class TankWarGame : public Game
{
	MeshActor* background;
	MusicSample* music;

public:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;
	Vector2f ComputeNormal(const FloatRect& _rect);
	float Length(const Vector2f& _vector);
};