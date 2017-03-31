#pragma once

#include "Attributed.h"
#include "WorldState.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		class Entity;
		class World;

		class Sector final : public Attributed
		{
		public:
			Sector(const std::string& name);
			~Sector() = default;

			Sector(const Sector&) = delete;
			Sector(Sector&&) = delete;
			Sector& operator==(const Sector&) = delete;
			Sector& operator==(const Sector&&) = delete;

			std::string Name() const;
			void SetName(const std::string& name);

			World& GetWorld();
			Datum& Entities();
			Entity& CreateEntity(const std::string& name, const std::string& className);
			void AdoptEntity(Entity& entity);
			void Update(WorldState& worldState);
		private:
			Datum* mEntities;
			std::string mName;

			static const std::string EntitiesAttributeName;

			ATTRIBUTED_DECLARATIONS(Sector, Attributed)
		};
	}
}
