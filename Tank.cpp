#include "Tank.h"

namespace Tank
{
	Tank::Tank()
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

	void Tank::Attachpart(const TankPart& _socketName, Actor* _part)
	{
		if (!_part) {
			cerr << "Erreur : tentative d'attacher un pointeur nul à " << _socketName << endl;
			return;
		}

		

		//this->AddChild(_part, AT_SNAP_TO_TARGET);
	}

	void Tank::Detachpart(const TankPart& _socketName)
	{
	}
}

