#pragma once

#include "Action.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		/** A switch case action implementation
		 */
		class EventAction : public Action
		{
		public:
			/** Initialize an event action with the given name
			 *  @param name The name of the action list
			 */
			EventAction(const std::string& name = "");
			/** Free up any allocated resources
			 */
			virtual ~EventAction() = default;

			// Delete move and copy semantics
			EventAction(const EventAction&) = delete;
			EventAction(EventAction&&) = delete;
			EventAction& operator=(const EventAction&) = delete;
			EventAction& operator=(EventAction&&) = delete;

			/** Generate an event of the configured type
			 *  @worldState The world context object that is passed for the update
			 */
			void Update(WorldState& worldState) override;
		private:
			// The expression to be evaluated for switch case
			std::string mSubtype;
			// The delay in milliseconds
			std::int32_t mDelay;

			ATTRIBUTED_DECLARATIONS(EventAction, Action)
		};

		ACTION_FACTORY_DECLARATIONS(EventAction)
	}
}
