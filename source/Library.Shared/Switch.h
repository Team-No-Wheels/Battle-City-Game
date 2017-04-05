#pragma once

#include "ActionList.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		class Switch : public ActionList
		{
		public:
			Switch(const std::string& name = "");
			virtual ~Switch() = default;

			Switch(const Switch&) = delete;
			Switch(Switch&&) = delete;
			Switch& operator==(const Switch&) = delete;
			Switch& operator==(const Switch&&) = delete;


			void Update(WorldState& worldState) override;
		private:
			std::string mExpression;
			Datum* mDefaultCase;

			ATTRIBUTED_DECLARATIONS(Switch, Action)
		};

		ACTION_FACTORY_DECLARATIONS(Switch)
	}
}
