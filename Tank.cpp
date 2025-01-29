#include "Tank.h"

namespace Tank
{
	Tank::Tank(const Vector2f& _size) : MeshActor(RectangleShapeData(_size))
	{
		life = 100.0f;
		isMoving = true;

		
	}

	Tank::~Tank()
	{
		/*for (const Actor* _element : this->GetChildren())
		{
			delete _element;
		}*/
	}

	void Tank::InitSocket()
	{
		map<TankPart, Vector2f> _socketPosition =
		{
			{Hull, Vector2f()},
			{Weapon, Vector2f()},
			{Track_Left, Vector2f()},
			{Track_Right, Vector2f()}
		};

		for (const pair<TankPart, Vector2f> _pos : _socketPosition)
		{
			Socket* _socket = new Socket(_pos.first);
			_socket->SetPosition(_pos.second);
			AddChild(_socket, AT_SNAP_TO_TARGET);
		}
	}

	void Tank::AttachPart(const TankPart& _socketName, Actor* _part)
	{
		if (!_part) return;

		

		//this->AddChild(_part, AT_SNAP_TO_TARGET);
	}

	void Tank::DetachPart(const TankPart& _socketName)
	{
		
	}
}

