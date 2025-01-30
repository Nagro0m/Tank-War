#pragma once
#include "MeshActor.h"
#include "AnimationComponent.h"

class Weapon : public MeshActor
{
	MeshActor* shoot;
	Animation* animation;

public:
	Weapon(const Vector2f& _size, const string& _path = "", const TextureExtensionType& _textureType = PNG
		  ,const bool _isRepeated = false, const IntRect& _rect = {});

	Weapon(const Weapon& _weapon);
public:
	void Move(const Vector2f _newPosition);
};

