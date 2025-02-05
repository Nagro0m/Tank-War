#include "Bullet.h"

Bullet::Bullet(const Vector2f& _direction) : MeshActor(RectangleShapeData(Vector2f(50.0f, 50.0f), "Tank/Bullet/Bullet"), "BulletActor"/* GetRandomNumberInRange(2, 6)*/)
{
	direction = _direction;
}

void Bullet::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	const Vector2f& _offset = direction * 150.0f * _deltaTime;
	Move(_offset);
}

void Bullet::Construct()
{
	Super::Construct();
}

void Bullet::Deconstruct()
{
	Super::Deconstruct();
}

void Bullet::BeginPlay()
{
	Super::BeginPlay();
}
