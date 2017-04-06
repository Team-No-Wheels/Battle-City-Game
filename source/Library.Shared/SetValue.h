#pragma once

#include "ActionList.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		/** A set value action implementation
		 */
		class SetValue : public Action
		{
		public:
			/** Initialize a set value action with the given name
			 *  @param name The name of the action
			 */
			SetValue(const std::string& name = "");
			/** Free up any allocated resources
			 */
			virtual ~SetValue() = default;

			// Delete move and copy semantics
			SetValue(const SetValue&) = delete;
			SetValue(SetValue&&) = delete;
			SetValue& operator==(const SetValue&) = delete;
			SetValue& operator==(const SetValue&&) = delete;

			/** Set the value of the given attribute
			 *  @worldState The world context object that is passed for the update
			 */
			void Update(WorldState& worldState) override;
		private:
			// The target attribute to be set
			std::string mTarget;
			// The value that the target is to be set to
			std::string mValue;
			// The index inside the target datum that is to be set
			std::int32_t mIndex;

			ATTRIBUTED_DECLARATIONS(SetValue, Action)
		};

		ACTION_FACTORY_DECLARATIONS(SetValue)
	}
}
