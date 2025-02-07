#include "Bullet.h"
#include "ExplosionAnimation.h"
#include "Level.h"
#include "Tank.h"

Bullet::Bullet(const Vector2f& _direction) : MeshActor(RectangleShapeData(Vector2f(50.0f, 50.0f), "Tank/Bullet/Bullet"), "BulletActor", GetRandomNumberInRange(2, 4))
{
	direction = _direction;
	movement = CreateComponent<MovementComponent>(500.0f);
	collision->SetInformation("Bullet", IS_ALL, CT_OVERLAP, true);
	SetLayer(Layer::LayerType::PROJECTILE);
	vector<pair<string, CollisionType>> _responsesMesh = { {"BardedWire", CT_BLOCK}, {"Tree", CT_BLOCK} ,{"Rock", CT_BLOCK}, { "Tank", CT_OVERLAP } };
	collision->AddResponses(_responsesMesh);
	isExplode = false;
	explosionNumber = 0;
}

Bullet::Bullet(const Bullet& _other) : MeshActor(_other)
{
	SetLayer(_other.GetLayer());
	direction = _other.direction;
	movement = CreateComponent<MovementComponent>(500.0f);
	explosionNumber = _other.explosionNumber;
	//collision = CreateComponent<CollisionComponent>(*_other.collision);
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
	if (!isExplode)
	{
		Explosion();
	}
	Super::Deconstruct();
}

void Bullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void Bullet::CollisionEnter(const CollisionData& _data)
{
	if (IsToDelete()) return;
}

void Bullet::CollisionUpdate(const CollisionData& _data)
{
	if (IsToDelete()) return;

	if (_data.response == CT_BLOCK)
	{
		if (_data.other->GetLayer() == Layer::LayerType::BREAKABLE)
		{
			_data.other->SetToDelete();
			SetToDelete();
			Explosion();
		}

		else if (_data.other->GetLayer() == Layer::LayerType::WORLD_STATIC)
		{
			SetToDelete();
			Explosion();
		}
	}

	else if (explosionNumber != 3)
	{
		++explosionNumber;
		return;
	}

	else if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{
			Tank* _tank = Cast<Tank>(_data.other);
			if (_tank)
			{
				SetToDelete();
				Explosion();
				_tank->ChangeLife(-1);
			}
		}
	}
	

}

void Bullet::CollisionExit(const CollisionData& _data)
{

}

void Bullet::Explosion()
{
	ExplosionAnimation* _explosion = Level::SpawnActor(ExplosionAnimation(RectangleShapeData(Vector2f(60, 60), "Effects/Explosion")));
	_explosion->SetOriginAtMiddle();
	_explosion->SetPosition(GetPosition());
}
