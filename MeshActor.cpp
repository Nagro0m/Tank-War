#include "MeshActor.h"
#include "CameraManager.h"
#include "CollisionComponent.h"
#include "ActorManager.h"

using namespace Camera;

MeshActor::MeshActor(const float _radius, const size_t& _pointCount, const string& _path,
	const IntRect& _rect, const string& _name) : Actor(_name)
{
	mesh = CreateComponent<MeshComponent>(_radius, _pointCount, _path, _rect);
	renderMeshToken = -1;
	collision = CreateComponent<CollisionComponent>();
}

MeshActor::MeshActor(const RectangleShapeData& _data, const string& _name, const float _lifespan) : Actor(_name, TransformData(), _lifespan)
{
	mesh = CreateComponent<MeshComponent>(_data);
	renderMeshToken = -1;
	collision = CreateComponent<CollisionComponent>();
}

MeshActor::MeshActor(const MeshActor& _other) : Actor(_other)
{
	mesh = CreateComponent<MeshComponent>(_other.mesh);
	renderMeshToken = _other.renderMeshToken;
	collision = CreateComponent<CollisionComponent>(*_other.collision);
}


void MeshActor::Construct()
{
	Super::Construct();

	const RenderData& _data = RenderData(bind(&MeshActor::RenderMesh, this, placeholders::_1));
	renderMeshToken = M_CAMERA.BindOnRenderWindow(_data);
	if (collision->GetChannelName() != "NONE")
	{
		M_ACTOR.AddCollisionComponent(collision);
	}
}

void MeshActor::Deconstruct()
{
	Super::Deconstruct();
	M_ACTOR.RemoveColiisionComponents(collision);
	M_CAMERA.UnbindOnRenderWindow(renderMeshToken);
}


void MeshActor::RenderMesh(RenderWindow& _window)
{
	_window.draw(*mesh->GetShape()->GetDrawable());
}