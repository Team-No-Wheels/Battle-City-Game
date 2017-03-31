#pragma once

#include "Attributed.h"
#include "Factory.h"
#include "WorldState.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		class Action;
		class Sector;

		class Entity : public Attributed
		{
		public:
			Entity(const std::string& name);
			~Entity() = default;

			Entity(const Entity&) = delete;
			Entity(Entity&&) = delete;
			Entity& operator==(const Entity&) = delete;
			Entity& operator==(const Entity&&) = delete;

			std::string Name() const;
			void SetName(const std::string& name);

			Sector& GetSector();
			void AdoptAction(Action& action);
			void Update(WorldState& worldState);
		private:
			Datum* mActions;
			std::string mName;

			static const std::string ActionsAttributeName;

			ATTRIBUTED_DECLARATIONS(Entity, Attributed)
		};

#define ENTITY_FACTORY_DECLARATIONS(ConcreteEntityT)		\
	CONCRETE_FACTORY_DECLARATIONS(Entity, ConcreteEntityT)

#define ENTITY_FACTORY_DEFINITIONS(ConcreteEntityT)		\
	CONCRETE_FACTORY_DEFINITIONS(Entity, ConcreteEntityT)

	}
}
