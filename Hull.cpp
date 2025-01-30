#include "Hull.h"

Tank::Hull::Hull(const Vector2f& _size, const string& _path, const TextureExtensionType& _textureType
		  ,const bool _isRepeated, const IntRect& _rect)
		  : TankPart(Hull_Part,RectangleShapeData(_size, _path, _textureType, _isRepeated, _rect))
{
}

void Tank::Hull::Move(const Vector2f _newPosition)
{

}