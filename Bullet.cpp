#include "Bullet.h"

Bullet::Bullet(const Vector2f& _direction) : MeshActor(RectangleShapeData(Vector2f(50.0f, 50.0f), "Tank/Bullet/Bullet"), "BulletActor", 50.0f)
{
	movement = CreateComponent<MovementComponent>(60.0f);
	movement->SetDirection(_direction);
}

void Bullet::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void Bullet::Construct()
{
	Super::Construct();
	movement->SetIsMoving(true);
}

void Bullet::Deconstruct()
{
	Super::Deconstruct();
}

void Bullet::BeginPlay()
{
	Super::BeginPlay();
}
