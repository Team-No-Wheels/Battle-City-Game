#include "Pch.h"
#include "MessageCollision.h"

using namespace AnonymousEngine;

MessageCollision::MessageCollision(Containers::WorldState& worldState):
	mEntities(5), mWorldState(worldState)
{

}

MessageCollision::~MessageCollision()
{

}

bool MessageCollision::operator==(const MessageCollision& rhs)
{
	if (mEntities.Size() != rhs.mEntities.Size())
		return false;

	for (std::uint32_t i = 0; i < mEntities.Size(); ++i)
	{
		if (mEntities[i] != rhs.mEntities[i])
		{
			return false;
		}
	}

	return true;
}

void MessageCollision::AddCollision( Entity& entity1, Entity& entity2)
{
	mEntities.PushBack(CollisionPair(&entity1, &entity2));
}

Vector<MessageCollision::CollisionPair>& MessageCollision::GetEntities()
{
	return mEntities;
}

Containers::WorldState& MessageCollision::WorldState()
{
	return mWorldState;
}