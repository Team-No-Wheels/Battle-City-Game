#pragma once

#include "Attributed.h"
#include "Entity.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		class Action : public Attributed
		{
		public:
			Action(const std::string& name);
			virtual ~Action() = default;

			Action(const Action&) = delete;
			Action(Action&&) = delete;
			Action& operator==(const Action&) = delete;
			Action& operator==(const Action&&) = delete;

			std::string Name() const;
			void SetName(const std::string& name);

			void AdoptAction(Action& action);
			virtual void Update(WorldState& worldState);
		private:
			Datum* mActions;
			std::string mName;

			static const std::string ActionsAttributeName;

			ATTRIBUTED_DECLARATIONS(Action, Attributed)
		};
	}
}
