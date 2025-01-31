#include "Tank.h"
#include "InputManager.h"
#include "CameraManager.h"
#include "TimerManager.h"

Tank::Tank(const string& _path) : MeshActor(RectangleShapeData(Vector2f(60.0f, 110.0f), _path))
{
	life = 100.0f;
	isMoving = false;
	movement = CreateComponent<MovementComponent>();
	speed = 1.0f;
	pitch = 1.0f;
	sound = nullptr;
}

void Tank::Construct()
{
	Super::Construct();

	SetOriginAtMiddle();
	PlaySample();
	SoundSample* _backgroundEngineSound = M_AUDIO.PlaySample<SoundSample>("Tank_Engine");
	_backgroundEngineSound->SetLoop(true);
	_backgroundEngineSound->SetVolume(5.0f);

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

	Move(move * speed * _deltaTime * 10.0f);
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
	if (speed >= 10) return;

	speed += 1;
	if (sound)
	{
		M_AUDIO.PlaySample<SoundSample>("Gear_Shift");
		if (pitch <= 1.9f)
		{
			pitch += 0.1f;
			cout << pitch << endl;
		}

		sound->SetPitch(pitch);
	}
}

void Tank::SlowDown()
{
	if (speed <= 1)
	{
		speed = 0;
		return;
	}
		
		
	speed -= 1;
	if (sound)
	{
		M_AUDIO.PlaySample<SoundSample>("Gear_Shift");
		if (pitch >= 0.8f)
		{
			pitch -= 0.1f;
		}
		sound->SetPitch(pitch);
		cout << pitch << endl;
	}
}

void Tank::PlaySample()
{
	sound = M_AUDIO.PlaySample<SoundSample>("Tank_Engine", WAV);
	sound->SetVolume(35.0f);
	sound->SetLoop(true);
}

