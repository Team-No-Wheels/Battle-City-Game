#pragma once

#include "GameTime.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		class World;
		class Sector;
		class Entity;
		class Action;

		/** Represents the current state of the processing in an update loop of the game
		 */
		class WorldState
		{
		public:
			/** Initialize a world state
			 */
			WorldState();

			/** Free any allocated resources
			 */
			~WorldState() = default;

			/** The current world that is being processed
			 */
			World* mWorld;

			/** The current sector that is being processed
			 */
			Sector* mSector;

			/** The current entity that is being processed
			 */
			Entity* mEntity;

			/** The current action that is being processed
			 */
			Action* mAction;

			/** The current time information for the processing methods
			 */
			GameTime mGameTime;
		};
	}
}
