#include "LoadAnimation.h"
#include "CameraManager.h"

using namespace Camera;

LoadAnimation::LoadAnimation(const RectangleShapeData& _data) : MeshActor(_data, "Effects/Load", 2.5f)
{
	animation = CreateComponent<AnimationComponent>();
}

LoadAnimation::LoadAnimation(const LoadAnimation& _other) : MeshActor(_other)
{
	animation = CreateComponent<AnimationComponent>();
}

void LoadAnimation::Construct()
{
	Super::Construct();

    const float _timeBetween = 0.041f;
    const Vector2i& _spriteSize = Vector2i(144, 144);
    const vector<SpriteData>& _spritesData =
    {
        SpriteData(_timeBetween, Vector2i(0, 0), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 1, 0), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 2, 0), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 3, 0), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 4, 0), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 5, 0), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 6, 0), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 7, 0), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 8, 0), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 9, 0), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 10, 0), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 11, 0), _spriteSize),

        SpriteData(_timeBetween, Vector2i(0, _spriteSize.y * 1), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 1, _spriteSize.y * 1), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 2, _spriteSize.y * 1), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 3, _spriteSize.y * 1), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 4, _spriteSize.y * 1), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 5, _spriteSize.y * 1), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 6, _spriteSize.y * 1), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 7, _spriteSize.y * 1), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 8, _spriteSize.y * 1), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 9, _spriteSize.y * 1), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 10, _spriteSize.y * 1), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 11, _spriteSize.y * 1), _spriteSize),

        SpriteData(_timeBetween, Vector2i(0, _spriteSize.y * 2), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 1, _spriteSize.y * 2), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 2, _spriteSize.y * 2), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 3, _spriteSize.y * 2), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 4, _spriteSize.y * 2), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 5, _spriteSize.y * 2), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 6, _spriteSize.y * 2), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 7, _spriteSize.y * 2), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 8, _spriteSize.y * 2), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 9, _spriteSize.y * 2), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 10, _spriteSize.y * 2), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 11, _spriteSize.y * 2), _spriteSize),

        SpriteData(_timeBetween, Vector2i(0, _spriteSize.y * 3), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 1, _spriteSize.y * 3), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 2, _spriteSize.y * 3), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 3, _spriteSize.y * 3), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 4, _spriteSize.y * 3), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 5, _spriteSize.y * 3), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 6, _spriteSize.y * 3), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 7, _spriteSize.y * 3), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 8, _spriteSize.y * 3), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 9, _spriteSize.y * 3), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 10, _spriteSize.y * 3), _spriteSize),
        SpriteData(_timeBetween, Vector2i(_spriteSize.x * 11, _spriteSize.y * 3), _spriteSize),
    };

	AnimationData _animationData = AnimationData(1.0f, _spritesData, true, false);

	animation->AddAnimation(new Animation("Load", GetMesh()->GetShape(), _animationData));
	animation->SetCurrentAnimation("Load");
	animation->StartAnimation();
}

void LoadAnimation::RenderMesh(RenderWindow& _window)
{
	Super::RenderMesh(_window);
}

void LoadAnimation::Deconstruct()
{
	Super::Deconstruct();
	animation->StopAnimation();
  
}


void LoadAnimation::BeginPlay()
{
	Super::BeginPlay();
}

void LoadAnimation::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}
