#include "Socket.h"

namespace Tank
{
	class Tank : public MeshActor
	{
		////Corps du tank
		//Hull* hull;
		////Canon
		//Weapon* weapon;
		////Chenilles
		//Track* track;

		int life;
		bool isMoving;

	public:
		FORCEINLINE set<Socket*> GetSocketByTankPart(const TankPart& _type)
		{
			set<Socket*> _socketsType;
			set<Actor*> _sockets = GetChildren();
			for (Actor* _socketActor : _sockets)
			{
				Socket* _socket = dynamic_cast<Socket*>(_socketActor);
				if (_socket->GetTankPartType() == _type)
				{
					_socketsType.insert(_socket);
				}
			}
			return _socketsType;
		}


	public:
		Tank();
		~Tank();

	public:
		void InitSocket();
		void Attachpart(const TankPart& _socketType, Actor* _part);
		void Detachpart(const TankPart& _socketType);
	};
}