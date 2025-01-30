#include "Weapon.h"

Tank::Weapon::Weapon(const Vector2f& _size, const string& _path, const TextureExtensionType& _textureType
			  ,const bool _isRepeated, const IntRect& _rect)
			  : TankPart(Weapon_Part,RectangleShapeData(_size, _path, _textureType, _isRepeated, _rect))
{

}

void Tank::Weapon::Move(const Vector2f _newPosition)
{
}
