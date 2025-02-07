#include "Weapon.h"

Weapon::Weapon(const Vector2f& _size, const string& _path) : MeshActor(RectangleShapeData(_size, _path), "TrackActor")
{
}

