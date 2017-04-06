#pragma once

#include "Action.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		/** An action that destroys an action
		 */
		class DestroyAction : public Action
		{
		public:
			/** Initialize an action destroy action with the given name
			 *  @param name The name of the action
			 */
			DestroyAction(const std::string& name = "");
			/** Free up any allocated resources
			 */
			virtual ~DestroyAction() = default;

			// Delete move and copy semantics
			DestroyAction(const DestroyAction&) = delete;
			DestroyAction(DestroyAction&&) = delete;
			DestroyAction& operator==(const DestroyAction&) = delete;
			DestroyAction& operator==(const DestroyAction&&) = delete;

			/** Destroy the action that is configured to be destroyed
			 *  @worldState The world context object that is passed for the update
			 */
			void Update(WorldState& worldState) override;
		private:
			// The name of this action
			std::string mInstanceName;

			ATTRIBUTED_DECLARATIONS(DestroyAction, Action)
		};

		ACTION_FACTORY_DECLARATIONS(DestroyAction)
	}
}
