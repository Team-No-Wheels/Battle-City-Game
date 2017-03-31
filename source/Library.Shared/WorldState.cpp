#include "WorldState.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		/** Represents the current state of the processing in an update loop of the game
		*/
		WorldState::WorldState() :
			mWorld(nullptr), mSector(nullptr), mEntity(nullptr), mAction(nullptr)
		{
		}
	}
}
