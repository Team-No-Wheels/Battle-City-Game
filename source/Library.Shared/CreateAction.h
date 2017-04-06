#pragma once

#include "Action.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		/** An action that creates an action
		 */
		class CreateAction : public Action
		{
		public:
			/** Initialize an action create action with the given name
			 *  @param name The name of the action
			 */
			CreateAction(const std::string& name = "");
			/** Free up any allocated resources
			 */
			virtual ~CreateAction() = default;

			// Delete move and copy semantics
			CreateAction(const CreateAction&) = delete;
			CreateAction(CreateAction&&) = delete;
			CreateAction& operator==(const CreateAction&) = delete;
			CreateAction& operator==(const CreateAction&&) = delete;

			/** Create an action that is configured to be created
			 *  @worldState The world context object that is passed for the update
			 */
			void Update(WorldState& worldState) override;
		private:
			// The name of the new action to be created
			std::string mInstanceName;
			// The type of the new action to be created
			std::string mClassName;

			ATTRIBUTED_DECLARATIONS(CreateAction, Action)
		};

		ACTION_FACTORY_DECLARATIONS(CreateAction)
	}
}
