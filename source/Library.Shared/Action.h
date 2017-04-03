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

			virtual void Update(WorldState& worldState) = 0;
		private:
			std::string mName;

			ATTRIBUTED_DECLARATIONS(Action, Attributed)
		};

#define ACTION_FACTORY_DECLARATIONS(ConcreteActionT)		\
	CONCRETE_FACTORY_DECLARATIONS(Action, ConcreteActionT)

#define ACTION_FACTORY_DEFINITIONS(ConcreteActionT)		\
	CONCRETE_FACTORY_DEFINITIONS(Action, ConcreteActionT)

	}
}
