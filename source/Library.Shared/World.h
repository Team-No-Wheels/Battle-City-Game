#pragma once

#include "Attributed.h"
#include "EventQueue.h"
#include "WorldState.h"

namespace AnonymousEngine
{
	namespace Audio
	{
		class AudioManager;
	}

	namespace Containers
	{
		class Sector;

		/** Defines a world class which sits at the top of the simulation
		 */
		class World final : public Attributed
		{
		public:
			/** Instantiate a world with a given name
			 *  @param name The name of the world. Defaulted to empty string
			 */
			World(const std::string& name);
			/** Free up any resources allocated by the instance
			 */
			~World() = default;

			// Delete move and copy semantics
			World(const World&) = delete;
			World(World&&) = delete;
			World& operator=(const World&) = delete;
			World& operator=(World&&) = delete;

			/** Get the name of the world
			 *  @return The name of the world
			 */
			std::string Name() const;
			/** Set the name of the world
			 *  @param name The new name to set
			 */
			void SetName(const std::string& name);

			/** Initializes the variables to load the game afresh.
			*/
			void InitializeWorld();

			/** Resets the variables to load next level.
			*/
			void LoadNextLevel();

			/** Return the list of sectors contained within this world
			 *  @return The list of sectors this world has
			 */
			Datum& Sectors() const;
			/** Create a sector with the given name and add it to this world
			 *  @param name The name of the sector to be created
			 *  @return A reference to the created sector
			 */
			Sector& CreateSector(const std::string& name);
			/** Adopts an existing sector to this world
			 *  @param sector The sector to adopt to this world
			 */
			void AdoptSector(Sector& sector);

			/** Return the list of actions contained within this world
			 *  @return The list of actions this world has
			 */
			Datum& Actions() const;

			/** Update the sectors and actions within this world
			 */
			void Update();

			/** Mark an attributed for delete
			 *  @param attributed The attributed object to delete
			 */
			void MarkForDelete(Attributed& attributed);

			/** Get the event queue in the world
			 *  @return A reference to the event queue in the world
			 */
			Core::EventQueue& EventQueue();

			/** Get the current world state in the simulation
			 *  @return The current world state
			 */
			WorldState& GetWorldState();

			/** The name of the sectors prescribed attribute
			 */
			static const std::string SectorsAttributeName;
		private:
			// The name of this world
			std::string mName;
			// The list of sectors contained by this instance
			Datum* mSectors;
			// The list of actions contained by this instance
			Datum* mActions;
			// The event queue in the world
			Core::EventQueue mEventQueue;
			// The current world state in the simulation
			WorldState mWorldState;

			// The garbage queue
			Vector<Attributed*> mGarbageQueue;
			// Mutex for garbage queue
			std::mutex mGarbageQueueMutex;

			ATTRIBUTED_DECLARATIONS(World, Attributed)
		};
	}
}