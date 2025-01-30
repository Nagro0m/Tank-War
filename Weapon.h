#pragma once
#include "AnimationComponent.h"
#include "TankPart.h"
namespace Tank
{
	class Weapon : public TankPart
	{
		MeshActor* Shoot;
		Animation* animation;

	public:
		Weapon(const Vector2f& _size, const string& _path = "", const TextureExtensionType& _textureType = PNG
			, const bool _isRepeated = false, const IntRect& _rect = {});
	public:
		void Move(const Vector2f _newPosition);
	};
}