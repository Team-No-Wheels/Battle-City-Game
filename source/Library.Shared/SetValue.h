#pragma once

#include "ActionList.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		class SetValue : public Action
		{
		public:
			SetValue(const std::string& name = "");
			virtual ~SetValue() = default;

			SetValue(const SetValue&) = delete;
			SetValue(SetValue&&) = delete;
			SetValue& operator==(const SetValue&) = delete;
			SetValue& operator==(const SetValue&&) = delete;


			void Update(WorldState& worldState) override;
		private:
			std::string mTarget;
			std::string mValue;
			std::int32_t mIndex;

			ATTRIBUTED_DECLARATIONS(SetValue, Action)
		};

		ACTION_FACTORY_DECLARATIONS(SetValue)
	}
}
