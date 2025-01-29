#pragma once
#include "MeshActor.h"

class Hull : public MeshActor
{
public:
	Hull(const Vector2f& _size, const string& _path = "", const TextureExtensionType& _textureType = PNG
		,const bool _isRepeated = false, const IntRect& _rect = {});

public:
	void Move(const Vector2f _newPosition);
};