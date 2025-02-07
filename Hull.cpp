#include "Hull.h"

Hull::Hull(const Vector2f& _size, const string& _path) : MeshActor(RectangleShapeData(_size, _path), "HullActor")
{
}

