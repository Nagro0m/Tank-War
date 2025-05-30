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
#include "MeshActor.h"
#include "ExplosionAnimation.h"

void Tank::SetHull(const string& _hull)
{
	MeshActor* _hullActor = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(120.0f, 120.0f), "Tank/" + _hull)));
	_hullActor->SetOriginAtMiddle();
	hull = _hull;
	AddChild(_hullActor, AttachmentType::AT_SNAP_TO_TARGET);
}

void Tank::SetWeapon(const string& _weapon)
{
	MeshActor* _weaponActor = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(40.0f, 90.0f), "Tank/" + _weapon)));
	_weaponActor->SetOriginAtMiddle();
	weapon = _weapon;
	AddChild(_weaponActor, AttachmentType::AT_SNAP_TO_TARGET);
}

Tank::Tank(vector<KeyType> _code, const string& _path, const string& _name, float _fuelTank) : MeshActor(RectangleShapeData(Vector2f(75.0f, 120.0f), _path, PNG, false, IntRect(Vector2i(0.0f, 0.0f), Vector2i(280, 384))))
{
	SetOriginAtMiddle();
	life = 100.0f;
	fuelTank = _fuelTank;
	isMoving = false;
	movement = CreateComponent<MovementComponent>(0.0f);

	collision->SetInformation("Tank", IS_ALL, CT_OVERLAP, true);
	pitch = 1.0f;
	sound = nullptr;
	rearSound = nullptr;
	maxSpeed = 100.0f;
	isReadyToShoot = true;
	code = _code;
	name = _name;
	track = _path;
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
	pitch = _other.pitch;
	sound = _other.sound;
	rearSound = _other.rearSound;
	maxSpeed = _other.maxSpeed;
	isReadyToShoot = _other.isReadyToShoot;
	code = _other.code;
	name = _other.name;
	distance = _other.distance;
	hull = _other.hull;
	weapon = _other.weapon;
	track = _other.track;
	SetLayer(_other.GetLayer());
}

void Tank::Construct()
{
	Super::Construct();

	SetOriginAtMiddle();
	PlaySample();
	CreateTrackAnimation();
	//SoundSample* _backgroundEngineSound = M_AUDIO.PlaySample<SoundSample>("Tank_Engine");
	//_backgroundEngineSound->SetLoop(true);
	//_backgroundEngineSound->SetVolume(5.0f);

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
	Die();
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
			if (movement->GetSpeed() != 0.0f) M_AUDIO.PlaySample<SoundSample>("Collision");
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

void Tank::CollisionUpdate(const CollisionData& _data)
{
	if (IsToDelete()) return;

	if (_data.response == CT_BLOCK)
	{

		if (_data.other->GetLayer() == Layer::LayerType::WORLD_STATIC)
		{
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

void Tank::CreateTrackAnimation()
{
	//const float _timeBetween = 0.0125f;
	//const Vector2i& _spriteSize = Vector2i(75, 120);
	//const vector<SpriteData>& _spritesData =
	//{
	//	SpriteData(_timeBetween,Vector2i(0, 0),_spriteSize),
	//	SpriteData(_timeBetween, Vector2i(0, 384),_spriteSize),
	//};

	//const AnimationData& _movingAnimationData = AnimationData(2.0f, _spritesData, true, false);
	//const AnimationData& _idleAnimationData = AnimationData(1, 1, SpriteData(_timeBetween, Vector2i(0, 384), _spriteSize));

	//animation->AddAnimation(new Animation("Moving", GetMesh()->GetShape(), _movingAnimationData));
	//animation->AddAnimation(new Animation("Idle", GetMesh()->GetShape(), _idleAnimationData));
	//animation->SetCurrentAnimation("Moving");
	//animation->StartAnimation();

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

	Bullet* _bullet = Level::SpawnActor(Bullet(movement->GetDirection(), this));
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
	sound->SetVolume(0.0f);
	sound->SetLoop(true);
}

void Tank::ChangeLife( float _offset)
{
	_offset *= 20;
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

void Tank::Die()
{
	if (life == 0)
	{
		ExplosionAnimation* _explosion = Level::SpawnActor(ExplosionAnimation(RectangleShapeData(Vector2f(500, 500), "Effects/Explosion")));
		_explosion->SetOriginAtMiddle();
		_explosion->SetPosition(GetPosition());
		/*Camera::M_CAMERA.GetCurrent()->SetTarget(nullptr);
		movement = nullptr;
		SetToDelete();*/
		life = -20;
	}
}
