#include "WorldState.h"

using namespace std;

namespace AnonymousEngine
{
	namespace Containers
	{
		/** Represents the current state of the processing in an update loop of the game
		*/
		WorldState::WorldState() :
			mWorld(nullptr), mSector(nullptr), mEntity(nullptr), mAction(nullptr), mCurrentLevel(0)
		{
		}

		uint32_t WorldState::GetCurrentLevel() const
		{
			return mCurrentLevel;
		};
	}
}
