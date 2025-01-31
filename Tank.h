#include "MeshActor.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"

class Tank : public MeshActor
{
	int life;
	bool isMoving;
	MovementComponent* movement;
	CollisionComponent* collisions;
public:


public:
	Tank(const string& _path);

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
};
