#pragma once

#include "Action.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		/** Implements an action which can hold other actions
		 */
		class ActionList : public Action
		{
		public:
			/** Initialize an action list with the given name
			 *  @param name The name of the action list
			 */
			ActionList(const std::string& name = "");
			/** Free up any allocated resources
			 */
			virtual ~ActionList() = default;

			// Delete move and copy semantics
			ActionList(const ActionList&) = delete;
			ActionList(ActionList&&) = delete;
			ActionList& operator=(const ActionList&) = delete;
			ActionList& operator=(ActionList&&) = delete;

			/** Return the list of actions contained within this action list
			 *  @return The list of actions this action list has
			 */
			Datum& Actions() const;
			/** Create an action with the given name and type and add it to this list
			 *  @param name The name of the action to be created
			 *  @param className The type of the action to be created
			 *  @return A reference to the created action
			 */
			Action& CreateAction(const std::string& name, const std::string& className);
			/** Adopts an existing action to this list
			 *  @param action The action to adopt to this list
			 */
			void AdoptAction(Action& action);

			/** Update the actions within this list
			 *  @worldState The world context object that is passed for the update
			 */
			void Update(WorldState& worldState) override;
		
		protected:
			/** The list of actions contained by this instance
			 */
			Datum* mActions;

			ATTRIBUTED_DECLARATIONS(ActionList, Action)
		};

		ACTION_FACTORY_DECLARATIONS(ActionList)
	}
}
