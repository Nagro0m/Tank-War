#include "Bullet.h"
#include "ExplosionAnimation.h"
#include "Level.h"

Bullet::Bullet(const Vector2f& _direction) : MeshActor(RectangleShapeData(Vector2f(50.0f, 50.0f), "Tank/Bullet/Bullet"), "BulletActor", GetRandomNumberInRange(2, 4))
{
	direction = _direction;
	movement = CreateComponent<MovementComponent>(500.0f);
}

Bullet::Bullet(const Bullet& _other) : MeshActor(_other)
{
	direction = _other.direction;
	movement = CreateComponent<MovementComponent>(500.0f);
}

void Bullet::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	

}

void Bullet::Construct()
{
	Super::Construct();

	movement->SetIsMoving(true);
	movement->SetDirection(direction);
}

void Bullet::Deconstruct()
{
	Explosion();
	Super::Deconstruct();
}

void Bullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void Bullet::Explosion()
{
	ExplosionAnimation* _explosion = Level::SpawnActor(ExplosionAnimation(RectangleShapeData(Vector2f(30, 30), "Effects/Explosion")));
	_explosion->SetOriginAtMiddle();
	_explosion->SetPosition(GetPosition());
}
