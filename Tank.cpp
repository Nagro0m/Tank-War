#include "Tank.h"
#include "InputManager.h"
#include "CameraManager.h"

Tank::Tank(const string& _path) : MeshActor(RectangleShapeData(Vector2f(60.0f, 110.0f), _path))
{
	life = 100.0f;
	isMoving = false;
	movement = CreateComponent<MovementComponent>();
}

void Tank::Construct()
{
	Super::Construct();



	SetOriginAtMiddle();

	M_INPUT.BindAction({ Code::Q }, bind(&Tank::Left, this));
	M_INPUT.BindAction({ Code::D }, bind(&Tank::Right, this));
}

void Tank::BeginPlay()
{
	Super::BeginPlay();
}

void Tank::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	Move(move * 0.5f);

}

void Tank::ComputeDirection(const float _rotation)
{
	Rotate(degrees(_rotation));
	float _radians = (GetRotation().asDegrees() - 90.0f) * 3.14159265f / 180.0f; // Convertir en radians
	Vector2f _direction = Vector2f(cos(_radians), sin(_radians));

	move = _direction;
}

void Tank::Right()
{
	ComputeDirection(2);
}

void Tank::Left()
{
	ComputeDirection(-2);
}

