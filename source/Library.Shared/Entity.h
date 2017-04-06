#pragma once

#include "Attributed.h"
#include "Factory.h"
#include "WorldState.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		class Action;
		class Sector;

		/** Defines an entity class which can be inherited or customized via xml to store data
		 */
		class Entity : public Attributed
		{
		public:
			/** Instantiate an entity with a given name
			 *  @param name The name of the entity. Defaulted to empty string
			 */
			Entity(const std::string& name = "");
			/** Free up any resources allocated by the instance
			 */
			~Entity() = default;

			// Delete move and copy semantics
			Entity(const Entity&) = delete;
			Entity(Entity&&) = delete;
			Entity& operator==(const Entity&) = delete;
			Entity& operator==(const Entity&&) = delete;

			/** Get the name of the entity
			 *  @return The name of the entity
			 */
			std::string Name() const;
			/** Set the name of the entity
			 *  @param name The new name to set
			 */
			void SetName(const std::string& name);

			/** Get the sector who owns this entity
			 *  @return A reference to the sector who owns this entity
			 */
			Sector& GetSector();
			/** Return the list of actions contained within this entity
			 *  @return The list of actions this entity has
			 */
			Datum& Actions();
			/** Create an action with the given name and type and add it to this entity
			 *  @param name The name of the action to be created
			 *  @param className The type of the action to be created
			 *  @return A reference to the created action
			 */
			Action& CreateAction(const std::string& name, const std::string& className);
			/** Adopts an existing action to this list
			 *  @param action The action to adopt to this list
			 */
			void AdoptAction(Action& action);

			/** Update the actions within this entity
			 *  @worldState The world context object that is passed for the update
			 */
			void Update(WorldState& worldState);
		private:
			/** The name of this entity
			 */
			std::string mName;
			/** The list of actions contained by this instance
			 */
			Datum* mActions;

			static const std::string ActionsAttributeName;

			ATTRIBUTED_DECLARATIONS(Entity, Attributed)
		};

#define ENTITY_FACTORY_DECLARATIONS(ConcreteEntityT)		\
	CONCRETE_FACTORY_DECLARATIONS(Entity, ConcreteEntityT)

#define ENTITY_FACTORY_DEFINITIONS(ConcreteEntityT)		\
	CONCRETE_FACTORY_DEFINITIONS(Entity, ConcreteEntityT)

		ENTITY_FACTORY_DECLARATIONS(Entity);

	}
}
