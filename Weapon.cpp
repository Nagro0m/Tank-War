#include "Weapon.h"

Weapon::Weapon(const Vector2f& _size, const string& _path, const TextureExtensionType& _textureType
			  ,const bool _isRepeated, const IntRect& _rect)
			  : MeshActor(RectangleShapeData(_size, _path, _textureType, _isRepeated, _rect), "Weapon")
{
	shoot = nullptr;
	animation = nullptr;
}

Weapon::Weapon(const Weapon& _weapon) : MeshActor(_weapon)
{
	shoot = _weapon.shoot;
	animation = _weapon.animation;
}

void Weapon::Move(const Vector2f _newPosition)
{
}
