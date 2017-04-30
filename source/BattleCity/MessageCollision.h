#pragma once
#include "Entity.h"
#include "WorldState.h"

namespace AnonymousEngine
{
	using namespace AnonymousEngine::Containers;

	class MessageCollision
	{
	private:
		typedef std::pair<Entity*, Entity*> CollisionPair;

		Vector<CollisionPair> mEntities;
		Containers::WorldState& mWorldState;

	public:

		MessageCollision(Containers::WorldState& worldState);
		bool operator==(const MessageCollision& rhs);
		~MessageCollision();

		void AddCollision( Entity& entity1, Entity& entity2);
		Vector<CollisionPair>& GetEntities();

		/** Return the world state
			@return The world state
		*/
		Containers::WorldState& WorldState();
	};
}
