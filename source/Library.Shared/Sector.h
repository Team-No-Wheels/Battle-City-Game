#pragma once

#include "Attributed.h"
#include "WorldState.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		class Entity;
		class World;

		/** Defines a sector class which is owned by a world in simulation
		 */
		class Sector final : public Attributed
		{
		public:
			/** Instantiate a sector with a given name
			 *  @param name The name of the sector. Defaulted to empty string
			 */
			Sector(const std::string& name);
			/** Free up any resources allocated by the instance
			 */
			~Sector() = default;

			// Delete move and copy semantics
			Sector(const Sector&) = delete;
			Sector(Sector&&) = delete;
			Sector& operator=(const Sector&) = delete;
			Sector& operator=(Sector&&) = delete;

			/** Get the name of the sector
			 *  @return The name of the sector
			 */
			std::string Name() const;
			/** Set the name of the sector
			 *  @param name The new name to set
			 */
			void SetName(const std::string& name);

			/** Get the world that owns this sector
			 *  @ return A reference to the world that owns this sector
			 */
			World& GetWorld();
			/** Return the list of entities contained within this sector
			 *  @return The list of entities this sector has
			 */
			Datum& Entities();
			/** Create an entity with the given name and type and add it to this sector
			 *  @param name The name of the entity to be created
			 *  @return A reference to the created entity
			 */
			Entity& CreateEntity(const std::string& name, const std::string& className);
			/** Adopts an existing entity to this sector
			 *  @param entity The entity to adopt to this sector
			 */
			void AdoptEntity(Entity& entity);

			/** Return the list of actions contained within this sector
			 *  @return The list of actions this sector has
			 */
			Datum& Actions();
			/** Update the entities and actions within this sector
			 *  @worldState The world context object that is passed for the update
			 */
			void Update(WorldState& worldState);

			/** The name of the prescribed attribute that stores the entities
			 */
			static const std::string EntitiesAttributeName;
		private:
			// The name of this sector
			std::string mName;
			// The list of entities within this sector
			Datum* mEntities;
			// The list of actions within this sector
			Datum* mActions;

			ATTRIBUTED_DECLARATIONS(Sector, Attributed)
		};
	}
}
