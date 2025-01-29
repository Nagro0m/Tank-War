#include "Tank.h"

namespace Tank
{
<<<<<<< Updated upstream
	Tank::Tank()
	{
		life = 100.0f;
		isMoving = true;
=======
	Tank::Tank(const Vector2f& _size) : MeshActor(RectangleShapeData(_size))
	{
		life = 100.0f;
		isMoving = true;

		
>>>>>>> Stashed changes
	}

	Tank::~Tank()
	{
		/*for (const Actor* _element : this->GetChildren())
		{
			delete _element;
		}*/
	}

<<<<<<< Updated upstream
	void Tank::Attachpart(const TankPart& _socketName, Actor* _part)
	{
		if (!_part) {
			cerr << "Erreur : tentative d'attacher un pointeur nul à " << _socketName << endl;
			return;
		}
=======
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
>>>>>>> Stashed changes

		

		//this->AddChild(_part, AT_SNAP_TO_TARGET);
	}

<<<<<<< Updated upstream
	void Tank::Detachpart(const TankPart& _socketName)
	{
=======
	void Tank::DetachPart(const TankPart& _socketName)
	{

>>>>>>> Stashed changes
	}
}

