#include "Tree.h"
#include "Tank.h"
#include "Level.h"

Tree::Tree(const RectangleShapeData& _data) : MeshActor(_data, "Tree")
{
	SetLayer(Layer::LayerType::BREAKABLE);
	vector<pair<string, CollisionType>> _responsesMesh = { { "Tank", CT_OVERLAP }, { "Bullet", CT_OVERLAP } };
	collision->SetInformation("Tree", IS_ALL, CT_BLOCK, false);
	collision->AddResponses(_responsesMesh);
}

Tree::Tree(const float _size, const string& _path) : MeshActor(_size, 30, _path, {}, "Tree")
{
	SetLayer(Layer::LayerType::BREAKABLE);
	vector<pair<string, CollisionType>> _responsesMesh = { { "Tank", CT_OVERLAP }, { "Bullet", CT_OVERLAP } };
	collision->SetInformation("Tree", IS_ALL, CT_BLOCK, false);
	collision->AddResponses(_responsesMesh);
}

Tree::Tree(const Tree& _other) : MeshActor(_other)
{
	SetLayer(_other.GetLayer());
}

void Tree::BeginPlay()
{
	Super::BeginPlay();
}

void Tree::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void Tree::CollisionEnter(const CollisionData& _data)
{
	if (IsToDelete()) return;

}

void Tree::CollisionUpdate(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{
			Tank* _tank = Cast<Tank>(_data.other);
			if (_tank && !_tank->HasMaxSpeed())
			{
				//M_AUDIO.PlaySample<SoundSample>("TreeOnMetal", WAV)->SetVolume(90.0f);
				_tank->ResetSpeed();
			}
		}
	}
}

void Tree::CollisionExit(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{

		}
	}
}
