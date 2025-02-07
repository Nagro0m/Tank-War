#include "Tank.h"
#include "CameraManager.h"
#include "TimerManager.h"
#include "MeshActor.h"
#include "Logger.h"
#include "TireTrack.h"
#include "GameHUD.h"
#include "ShootAnimation.h"
#include "LoadAnimation.h"
#include "Layer.h"

Tank::Tank(vector<KeyType> _code, const string& _path, const string& _name, float _fuelTank) : MeshActor(RectangleShapeData(Vector2f(60.0f, 110.0f), _path))
{
	life = 100.0f;
	fuelTank = _fuelTank;
	isMoving = false;
	movement = CreateComponent<MovementComponent>(0.0f);
	//collision = CreateComponent<CollisionComponent>("Tank", IS_ALL, CT_OVERLAP);
	collision->SetInformation("Tank", IS_ALL, CT_OVERLAP, true);
	pitch = 1.0f;
	sound = nullptr;
	rearSound = nullptr;
	maxSpeed = 100.0f;
	isReadyToShoot = true;
	code = _code;
	name = _name;
	distance = 0.0f;
	SetLayer(Layer::LayerType::PLAYER);

	vector<pair<string, CollisionType>> _responsesTank = {{"BardedWire", CT_BLOCK}, {"Root", CT_BLOCK}, {"Grass", CT_BLOCK} , {"Tree", CT_BLOCK} ,{"Rock", CT_BLOCK}, {"Bullet", CT_OVERLAP} };
	collision->AddResponses(_responsesTank);
}

Tank::Tank(const Tank& _other) : MeshActor(_other)
{
	life = _other.life;
	fuelTank = _other.fuelTank;
	isMoving = _other.isMoving;
	movement = CreateComponent<MovementComponent>(_other.movement);
	collision = CreateComponent<CollisionComponent>(*_other.collision);
	//animation = CreateComponent<AnimationComponent>(_other.animation);
	pitch = _other.pitch;
	sound = _other.sound;
	rearSound = _other.rearSound;
	maxSpeed = _other.maxSpeed;
	isReadyToShoot = _other.isReadyToShoot;
	code = _other.code;
	name = _other.name;
	distance = _other.distance;

	SetLayer(_other.GetLayer());
}

void Tank::Construct()
{
	Super::Construct();

	SetOriginAtMiddle();
	PlaySample();
	SoundSample* _backgroundEngineSound = M_AUDIO.PlaySample<SoundSample>("Tank_Engine");
	_backgroundEngineSound->SetLoop(true);
	_backgroundEngineSound->SetVolume(5.0f);

	ActionMap* _actionMap = M_INPUT.CreateActionMap("Tank_" + name);

	_actionMap->AddAction("Left", ActionData(KeyHold, code[0]), [&]() { Left(); });
	_actionMap->AddAction("Right", ActionData(KeyHold, code[1]), [&]() { Right(); });
	_actionMap->AddAction("SpeedUp", ActionData(KeyPressed, code[2]), [&]() { SpeedUp(); });
	_actionMap->AddAction("SlowDown", ActionData(KeyPressed, code[3]), [&]() { SlowDown(); });
	_actionMap->AddAction("Shoot", ActionData(KeyPressed, code[4]), [&]() { Shoot(); });

	_actionMap->Enable();
	
	ComputeDirection(0.0f);
	M_GAMEHUD.ChangeLifeBarWithLife(name, life);
}

void Tank::Deconstruct()
{
	Super::Deconstruct();
	//animation->StopAnimation();
}

void Tank::BeginPlay()
{
	Super::BeginPlay();

}

void Tank::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	movement->SetIsMoving(isMoving);
	
	if (fuelTank != -1.0f)
	{
		UpdateFuelTank(_deltaTime);
	}

	distance += (1) * movement->GetSpeed();
	SpawnTireTrack();
}

void Tank::CollisionEnter(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_BLOCK)
	{
		if (_data.other->GetLayer() == Layer::LayerType::BREAKABLE)
		{
			if (HasMaxSpeed())
			{
				_data.other->SetToDelete();
			}
		}

		if (_data.other->GetLayer() == Layer::LayerType::WORLD_STATIC)
		{
			M_AUDIO.PlaySample<SoundSample>("Collision")->SetVolume(90.0f);
			ResetSpeed();
		}

	}

	else if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::RETRIEVABLE)
		{

		}

		if (_data.other->GetLayer() == Layer::LayerType::PROJECTILE)
		{
		}
	}
	
	distance += (1 ) * movement->GetSpeed();
	SpawnTireTrack();
}

void Tank::CollisionUpdate(const CollisionData& _data)
{
	if (IsToDelete()) return;

	if (_data.response == CT_BLOCK)
	{

		if (_data.other->GetLayer() == Layer::LayerType::WORLD_STATIC)
		{
			M_AUDIO.PlaySample<SoundSample>("Collision")->SetVolume(90.0f);
			ResetSpeed();
		}
	}

	else if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::RETRIEVABLE)
		{

		}

		if (_data.other->GetLayer() == Layer::LayerType::PROJECTILE)
		{
		}
	}
}

void Tank::CollisionExit(const CollisionData& _data)
{
	if (IsToDelete()) return;
}

void Tank::ComputeDirection(const float _rotation)
{
	Rotate(degrees(_rotation));
	float _radians = (GetRotation().asDegrees() - 90.0f) * pi / 180.0f;
	Vector2f _direction = Vector2f(cos(_radians), sin(_radians));
	movement->SetDirection(_direction);

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
	float _speed = movement->GetSpeed();
	isMoving = (_speed != 1);

	if (GetSpeed() >= maxSpeed) return;

	if (rearSound)
	{
		rearSound->Stop();
		rearSound = nullptr;
	}

	movement->SetSpeed(_speed + 10.0f);

	if (sound)
	{
		M_AUDIO.PlaySample<SoundSample>("Gear_Shift", WAV);
		if (pitch <= 1.9f)
		{
			pitch += 0.1f;
		}
		sound->SetPitch(pitch);
	}
}

void Tank::SlowDown()
{
	float _speed = movement->GetSpeed();

	if (_speed <= -10.0f)
	{
		_speed = -10.0f;
	}
	else
	{
		_speed -= 10.0f;
	}

	//if (_speed == 0)
	//{
	//	isMoving = false;
	//}

	movement->SetSpeed(_speed);
	isMoving = (_speed != 1);

	if (_speed < 0)
	{
		if (!rearSound)
		{
			rearSound = M_AUDIO.PlaySample<SoundSample>("RearSound");
		}
	}
	else if (rearSound)
	{
		rearSound->Stop();
		rearSound = nullptr;
	}

	if (sound)
	{
		M_AUDIO.PlaySample<SoundSample>("Gear_Shift", WAV);
		if (pitch >= 0.8f)
		{
			pitch -= 0.1f;
		}
		sound->SetPitch(pitch);
	}
}

void Tank::Shoot()
{
	if (!isReadyToShoot)
	{
		M_AUDIO.PlaySample<SoundSample>("EmptyWeapon");
		return;
	}
	isReadyToShoot = false;
	M_AUDIO.PlaySample<SoundSample>("Shoot");

	const Vector2f& _canonPosition = GetPosition() + movement->GetDirection() * 56.0f;

	Bullet* _bullet = Level::SpawnActor(Bullet(movement->GetDirection()));
	_bullet->SetRotation(GetRotation());
	_bullet->SetOriginAtMiddle();
	_bullet->SetPosition(_canonPosition);

	ShootAnimation* _shoot = Level::SpawnActor(ShootAnimation(RectangleShapeData(Vector2f(100.0f, 100.0f), "Effects/Shoot")));
	_shoot->SetOriginAtMiddle();
	_shoot->SetPosition(GetPosition() + movement->GetDirection() * 65.0f);
	_shoot->SetRotation(GetRotation() - degrees(90));
	
	new Timer(bind(&Tank::SetIsReadyToShoot, this), seconds(2), true);

}

void Tank::PlaySample()
{
	sound = M_AUDIO.PlaySample<SoundSample>("Tank_Engine", WAV);
	sound->SetVolume(35.0f);
	sound->SetLoop(true);
}

void Tank::ChangeLife(const float _offset)
{
	life = clamp(life + _offset, 0.0f, 100.0f);
	M_GAMEHUD.ChangeLifeBarWithLife(name, life);
}

void Tank::UpdateFuelTank(const float _deltaTime)
{
	const float _speed = movement->GetSpeed();
	fuelTank = _speed > 0 ? fuelTank - (maxSpeed - _speed + 1)* _deltaTime : fuelTank - 1 * _deltaTime;
	fuelTank = fuelTank <= 0 ? 0 : fuelTank;
	if (fuelTank == 0) isMoving = false;
	LOG(Display, to_string(fuelTank));
}

void Tank::Refuel()
{
	fuelTank = fuelTank + 50 > 100 ? 100 : fuelTank + 50;
	LOG(Display, to_string(fuelTank));
}

void Tank::SpawnTireTrack()
{
	distance < 0 ? distance = 0 : distance;

	if (distance >= 50 )
	{
		MeshActor* _effect = Level::SpawnActor(TireTrack(RectangleShapeData(Vector2f(55, 11), "Effects/TrackMark"), "shit", 5.0f));
		_effect->GetMesh()->GetShape()->GetDrawable()->setFillColor(Color(123, 63, 0, 100));
		_effect->SetOriginAtMiddle();
		_effect->SetPosition(GetPosition() - movement->GetDirection() * 56.0f);
		_effect->Rotate(GetRotation());
		distance = 0;
	}
	
}