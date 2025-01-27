#include "TankWarGame.h"

void TankWarGame::Start()
{
	level = Level();
	level.GenerateLevel();
	Super::Start();
}

bool TankWarGame::Update()
{
	Super::Update();
	return false;
}

void TankWarGame::Stop()
{
	Super::Stop();
}

Vector2f TankWarGame::ComputeNormal(const FloatRect& _rect)
{
	return Vector2f();
}

float TankWarGame::Length(const Vector2f& _vector)
{
	return 0.0f;
}
