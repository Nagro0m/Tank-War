#include "Track.h"

Track::Track(const Vector2f& _size, const string& _path) : MeshActor(RectangleShapeData(_size, _path, PNG, false, IntRect(Vector2i(0, 0), Vector2i(280, 385))), "TrackActor")
{
	animation = CreateComponent<AnimationComponent>();
	isMoving = false;
}

Track::Track(const Track& _other) : MeshActor(_other)
{
	animation = _other.animation;
	isMoving = _other.isMoving;
}

void Track::Construct()
{
	Super::Construct();
	//const float _timeBetween = 0.01f;
	//const Vector2i& _spriteSize = Vector2i(44, 248);
	//const SpriteData& _spriteData = SpriteData(Vector2i(44, 0), _spriteSize, _timeBetween);

	//AnimationData _animationDataIdle = AnimationData(1, 0.2f, _spriteData, false, true);
	//AnimationData _animationDataMoving = AnimationData(2, 0.2f, _spriteData, false, true);

	//animation->AddAnimation(new Animation("Idle", GetMesh()->GetShape(), _animationDataIdle));
	//animation->AddAnimation(new Animation("Moving", GetMesh()->GetShape(), _animationDataMoving));

	//animation->SetCurrentAnimation("Idle");
	//animation->StartAnimation();
}

void Track::Deconstruct()
{
	Super::Deconstruct();
	//animation->StopAnimation();
}

void Track::BeginPlay()
{
	Super::BeginPlay();
}