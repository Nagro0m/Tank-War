#include "MeshActor.h"
#include "Game.h"

MeshActor::MeshActor(const float _radius, const size_t& _pointCount,
	const string& _path, const IntRect& _rect)
{
	mesh = new MeshComponent(this, _radius, _path, _pointCount, _rect);
	AddComponent(mesh);
	renderMeshToken = M_GAME.BindOnRenderWindow(bind(&MeshActor::RenderMesh, this, placeholders::_1));
}

MeshActor::MeshActor(const Vector2f& _size, const string& _path, const IntRect& _rect)
{
	mesh = new MeshComponent(this, _size, _path, _rect);
	AddComponent(mesh);
	renderMeshToken = M_GAME.BindOnRenderWindow(bind(&MeshActor::RenderMesh, this, placeholders::_1));
}

MeshActor::~MeshActor()
{
	M_GAME.UnbindOnRenderWindow(renderMeshToken);
}

void MeshActor::RenderMesh(RenderWindow& _window)
{
	_window.draw(*mesh->GetShape()->GetDrawable());
}
