#include "Tank.h"


namespace Tank
{
	Tank::Tank()
	{
		life = 100.0f;
		isMoving = true;
		InitSocket();
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
		AddChild(new Socket(Hull), AT_SNAP_TO_TARGET);
	}

	void Tank::Attachpart(const TankPart& _socketType, Actor* _part)
	{
		if (!_part) {
			cerr << "Erreur : tentative d'attacher un pointeur nul" << _socketType << endl;
			return;
		}

		set<Socket*> _sockets = GetSocketByTankPart(_socketType);

		for (Socket* _socket : _sockets)
		{
			_socket->AddChild(_part, AT_SNAP_TO_TARGET);
		}
	}

	void Tank::Detachpart(const TankPart& _socketType)
	{
	}
}