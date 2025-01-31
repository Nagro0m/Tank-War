#include "Tank.h"

Tank::Tank(const string& _path) : MeshActor(RectangleShapeData(Vector2f(100.0f, 150.0f), _path))
{
	life = 100.0f;
	isMoving = false;
}

void Tank::BeginPlay()
{
	Super::BeginPlay();
}

void Tank::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}
