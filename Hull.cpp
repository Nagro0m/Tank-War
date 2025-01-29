#include "Hull.h"

Hull::Hull(const Vector2f& _size, const string& _path, const TextureExtensionType& _textureType
		  ,const bool _isRepeated, const IntRect& _rect)
		  : MeshActor(RectangleShapeData(_size, _path, _textureType, _isRepeated, _rect), "Hull")
{
}

void Hull::Move(const Vector2f _newPosition)
{

}