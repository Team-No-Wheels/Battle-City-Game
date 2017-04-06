#pragma once

#include "ActionList.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		/** A switch case action implementation
		 */
		class Switch : public ActionList
		{
		public:
			/** Initialize a switch action list with the given name
			 *  @param name The name of the action list
			 */
			Switch(const std::string& name = "");
			/** Free up any allocated resources
			 */
			virtual ~Switch() = default;

			// Delete move and copy semantics
			Switch(const Switch&) = delete;
			Switch(Switch&&) = delete;
			Switch& operator==(const Switch&) = delete;
			Switch& operator==(const Switch&&) = delete;

			/** Evaluate switch case and execute appropriate actions
			 *  @worldState The world context object that is passed for the update
			 */
			void Update(WorldState& worldState) override;
		private:
			// The expression to be evaluated for switch case
			std::string mExpression;
			// The default action
			Datum* mDefaultCase;

			ATTRIBUTED_DECLARATIONS(Switch, Action)
		};

		ACTION_FACTORY_DECLARATIONS(Switch)
	}
}
