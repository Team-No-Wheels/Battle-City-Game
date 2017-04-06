#pragma once

#include "Attributed.h"
#include "Entity.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		/** Defines an abstract interface for actions
		 */
		class Action : public Attributed
		{
		public:
			/** Instantiate an action with a given name
			 *  @param name The name of the action. Defaulted to empty string
			 */
			Action(const std::string& name = "");
			/** Free up any resources allocated by the instance
			 */
			virtual ~Action() = default;

			// Delete move and copy semantics
			Action(const Action&) = delete;
			Action(Action&&) = delete;
			Action& operator==(const Action&) = delete;
			Action& operator==(const Action&&) = delete;

			/** Get the name of the action
			 *  @return The name of the action
			 */
			std::string Name() const;
			/** Set the name of the action
			 *  @param name The new name to set
			 */
			void SetName(const std::string& name);

			/** Abstract update method to be implemented by all actions
			 *  @param worldState The world context object that will be passed into the update
			 */
			virtual void Update(WorldState& worldState) = 0;

			/** The prescribed attribute name used in the world, sector, entity hierrarchy to store the list of actions
			 */
			static const std::string ActionsAttributeName;

		protected:
			/** The name of this action
			 */
			std::string mName;

			ATTRIBUTED_DECLARATIONS(Action, Attributed)
		};

#define ACTION_FACTORY_DECLARATIONS(ConcreteActionT)		\
	CONCRETE_FACTORY_DECLARATIONS(Action, ConcreteActionT)

#define ACTION_FACTORY_DEFINITIONS(ConcreteActionT)		\
	CONCRETE_FACTORY_DEFINITIONS(Action, ConcreteActionT)

	}
}
