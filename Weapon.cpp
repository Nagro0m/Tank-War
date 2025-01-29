#include "Weapon.h"

Weapon::Weapon(const Vector2f& _size, const string& _path, const TextureExtensionType& _textureType
			  ,const bool _isRepeated, const IntRect& _rect)
			  : MeshActor(RectangleShapeData(_size, _path, _textureType, _isRepeated, _rect), "Weapon")
{

}

void Weapon::Move(const Vector2f _newPosition)
{
}
