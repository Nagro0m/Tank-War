#include "MeshComponent.h"
MeshComponent::MeshComponent(Actor* _owner, const float _radius, const string& _path,
	const size_t& _pointCount, const IntRect& _rect)
	: Component(_owner)
{
	shape = new ShapeObject(_radius, _path, _pointCount, _rect);
}

MeshComponent::MeshComponent(Actor* _owner, const Vector2f& _size, const string& _path,
	const IntRect& _rect)
	: Component(_owner)
{
	shape = new ShapeObject(_size, _path, _rect);
}

MeshComponent::~MeshComponent()
{
	delete shape;
}
