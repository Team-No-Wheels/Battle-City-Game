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
			Action(const std::string& name = "");
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

#define ACTION_FACTORY_DECLARATIONS(ConcreteActionT)		\
	CONCRETE_FACTORY_DECLARATIONS(Action, ConcreteActionT)

#define ACTION_FACTORY_DEFINITIONS(ConcreteActionT)		\
	CONCRETE_FACTORY_DEFINITIONS(Action, ConcreteActionT)

		ACTION_FACTORY_DECLARATIONS(Action)

	}
}
