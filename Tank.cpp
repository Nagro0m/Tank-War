#include "Tank.h"
#include "InputManager.h"
#include "CameraManager.h"

Tank::Tank(const string& _path) : MeshActor(RectangleShapeData(Vector2f(60.0f, 110.0f), _path))
{
	life = 100.0f;
	isMoving = false;
	movement = CreateComponent<MovementComponent>();
	speed = 1.0f;
}

void Tank::Construct()
{
	Super::Construct();



	SetOriginAtMiddle();

	M_INPUT.BindAction({ Code::Q }, bind(&Tank::Left, this));
	M_INPUT.BindAction({ Code::D }, bind(&Tank::Right, this));
	M_INPUT.BindAction({ Code::Z }, bind(&Tank::SpeedUp, this));
	M_INPUT.BindAction({ Code::S }, bind(&Tank::SlowDown, this));
}

void Tank::BeginPlay()
{
	Super::BeginPlay();
}

void Tank::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	Move(move * 0.1f * speed);
	cout << "vitesse : " << to_string(speed) << endl;

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

void Tank::SpeedUp()
{
	speed >= 10 ? speed = 10 : speed += 2;
}

void Tank::SlowDown()
{
	speed <= 1 ? speed = 0 : speed -= 2;
}

