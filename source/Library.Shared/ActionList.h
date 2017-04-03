#pragma once

#include "Action.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		class ActionList : public Action
		{
		public:
			ActionList(const std::string& name = "");
			virtual ~ActionList() = default;

			ActionList(const ActionList&) = delete;
			ActionList(ActionList&&) = delete;
			ActionList& operator==(const ActionList&) = delete;
			ActionList& operator==(const ActionList&&) = delete;

			Datum& Actions();
			Action& CreateAction(const std::string& name, const std::string& className);
			void AdoptAction(Action& action);
			void Update(WorldState& worldState) override;
		private:
			Datum* mActions;

			static const std::string ActionsAttributeName;

			ATTRIBUTED_DECLARATIONS(ActionList, Action)
		};

		ACTION_FACTORY_DECLARATIONS(ActionList)
	}
}
