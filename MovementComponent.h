#pragma once
#include "Component.h"

class MovementComponent : public Component
{
	float speed;
	Vector2f direction;
	bool isMoving;

public:
	FORCEINLINE void SetSpeed(const float _speed)
	{
		speed = _speed;
	}
	FORCEINLINE void SetDirection(const Vector2f& _direction)
	{
		direction = _direction;
	}
	FORCEINLINE void SetIsMoving(const bool _isMoving)
	{
		isMoving = _isMoving;
	}

	FORCEINLINE float GetSpeed() const
	{
		return speed;
	}
	FORCEINLINE Vector2f GetDirection() const
	{
		return direction;
	}

public:
	MovementComponent(Actor* _owner);
	MovementComponent(Actor* _owner, const float _speed);
	MovementComponent(Actor* _owner, const MovementComponent* _other);

protected:
	virtual void Tick(const float _deltaTime) override;

private:
	void Move(const float _deltaTime);
};