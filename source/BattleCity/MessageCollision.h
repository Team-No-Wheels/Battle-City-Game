#pragma once
#include "Entity.h"
#include "EventMessageAttributed.h"

namespace BattleCity
{
	using namespace AnonymousEngine::Containers;

	class AnonymousEngine::Containers::WorldState;

	class MessageCollision : public EventMessageAttributed
	{
		ATTRIBUTED_DECLARATIONS(MessageCollision, EventMessageAttributed)
	private:
		typedef std::pair<Entity*, Entity*> CollisionPair;

		AnonymousEngine::Vector<CollisionPair> mEntities;
		WorldState& mWorldState;

	public:

		MessageCollision(WorldState& worldState);
		bool operator==(const MessageCollision& rhs);
		~MessageCollision();

		void AddCollision( Entity& entity1, Entity& entity2);
		AnonymousEngine::Vector<CollisionPair>& GetEntities();

		/** Return the world state
			@return The world state
		*/
		WorldState& WorldState();
	};
}
