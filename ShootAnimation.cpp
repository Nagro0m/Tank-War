#include "ShootAnimation.h"

ShootAnimation::ShootAnimation(const RectangleShapeData& _data ) : MeshActor(_data, "Effects/Shoot")
{
	SetLifeSpan(0.2f);
	animation = CreateComponent<AnimationComponent>();
}

ShootAnimation::ShootAnimation(const ShootAnimation& _other) : MeshActor(_other)
{
	SetLifeSpan(0.2f);
	animation = CreateComponent<AnimationComponent>();

}

void ShootAnimation::Construct()
{
	Super::Construct();

	const float _timeBetween = 0.0125f;
	const Vector2i& _spriteSize = Vector2i(258, 258);
	const vector<SpriteData>& _spritesData =
	{
		SpriteData( Vector2i(0, 0),_spriteSize, _timeBetween),
		SpriteData(Vector2i(0, 258),_spriteSize, _timeBetween),
		SpriteData(Vector2i(0, 516),_spriteSize, _timeBetween),
		SpriteData(Vector2i(0, 774),_spriteSize, _timeBetween),
	};

	const AnimationData& _animationData = AnimationData(2.0f, _spritesData, true, false);
	

	animation->AddAnimation(new Animation("Default", GetMesh()->GetShape(), _animationData));
	animation->SetCurrentAnimation("Default");
	animation->StartAnimation();
}
void ShootAnimation::RenderMesh(RenderWindow& _window)
{
	Super::RenderMesh(_window);
}



void ShootAnimation::Deconstruct()
{
	Super::Deconstruct();
	animation->StopAnimation();

	
}

void ShootAnimation::BeginPlay()
{
	Super::BeginPlay();
}

void ShootAnimation::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}
