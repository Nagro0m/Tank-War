#include "ExplosionAnimation.h"
#include "AudioManager.h"


ExplosionAnimation::ExplosionAnimation(const RectangleShapeData& _data) : MeshActor(_data, "Effects/Explosion", 0.5f)
{
	animation = CreateComponent<AnimationComponent>();
}

ExplosionAnimation::ExplosionAnimation(const ExplosionAnimation& _other) : MeshActor(_other)
{
	animation = CreateComponent<AnimationComponent>();
}

void ExplosionAnimation::Construct()
{
	Super::Construct();

	const float _timeBetween = 0.1f;
	const Vector2i& _spriteSize = Vector2i(258, 258);
	const vector<SpriteData>& _spritesData =
	{
		SpriteData(_timeBetween, Vector2i(0, 0),_spriteSize),
		SpriteData(_timeBetween,Vector2i(258, 0),_spriteSize),
		SpriteData(_timeBetween,Vector2i(516, 0),_spriteSize),
		SpriteData(_timeBetween,Vector2i(774, 0),_spriteSize),
		SpriteData(_timeBetween,Vector2i(1032, 0),_spriteSize),
		SpriteData(_timeBetween,Vector2i(1290, 0),_spriteSize),
		SpriteData(_timeBetween,Vector2i(1548, 0),_spriteSize),
		SpriteData(_timeBetween,Vector2i(1806, 0),_spriteSize),
		SpriteData(_timeBetween,Vector2i(2064, 0),_spriteSize),
	};

	AnimationData _animationData = AnimationData(1.0f, _spritesData, true, false);
	_animationData.notifies[1] = []()
		{
			M_AUDIO.PlaySample<SoundSample>("Explosion");
		};

	animation->AddAnimation(new Animation("Explosion", GetMesh()->GetShape(), _animationData));
	animation->SetCurrentAnimation("Explosion");
	animation->StartAnimation();
}

void ExplosionAnimation::RenderMesh(RenderWindow& _window)
{
	Super::RenderMesh(_window);

}

void ExplosionAnimation::Deconstruct()
{
	Super::Deconstruct();
	animation->StopAnimation();
}

void ExplosionAnimation::BeginPlay()
{
	Super::BeginPlay();
}

void ExplosionAnimation::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}
