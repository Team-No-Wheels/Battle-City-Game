#pragma once
#include "Entity.h"

namespace AnonymousEngine
{
	using namespace AnonymousEngine::Containers;

	class MessageCollision
	{
	private:
		typedef std::pair<Entity*, Entity*> CollisionPair;

		Vector<CollisionPair> mEntities;

	public:

		MessageCollision();
		bool operator==(const MessageCollision& rhs);
		~MessageCollision();

		void AddCollision( Entity& entity1, Entity& entity2);
		Vector<CollisionPair>& GetEntities();

	};
}
