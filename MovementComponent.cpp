#include "MovementComponent.h"
#include "Actor.h"

MovementComponent::MovementComponent(Actor* _owner) : Component(_owner)
{
	canMove = true;
	speed = 0.0f;
	maxSpeed = 5.0f;
	mass = 54000.0f;
	gravity = 9.81f;
	direction = Vector2f(1.0f, 0.0f);
}

MovementComponent::MovementComponent(Actor* _owner, const MovementComponent* _other) : Component(_owner)
{
	canMove = _other->canMove;
	speed = _other->speed;
	maxSpeed = _other->maxSpeed;
	mass = _other->mass;
	gravity = _other->gravity;
	direction = _other->direction;
}


void MovementComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (canMove)
	{
		Move(_deltaTime);
	}
}


void MovementComponent::Move(const float _deltaTime)
{
	const Vector2f& _offset = direction * speed * _deltaTime;
	owner->Move(_offset);
}