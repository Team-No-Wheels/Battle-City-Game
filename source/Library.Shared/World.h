#pragma once

#include "Attributed.h"
#include "WorldState.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		class Sector;

		class World final : public Attributed
		{
		public:
			World(const std::string& name);
			~World() = default;

			World(const World&) = delete;
			World(World&&) = delete;
			World& operator==(const World&) = delete;
			World& operator==(const World&&) = delete;

			std::string Name() const;
			void SetName(const std::string& name);

			Datum& Sectors();
			Sector& CreateSector(const std::string& name);
			void AdoptSector(Sector& sector);
			void Update(WorldState& worldState);

			void MarkForDelete(Attributed& attributed);
		private:
			std::string mName;
			Datum* mSectors;

			Vector<Attributed*> mGarbageQueue;

			static const std::string SectorsAttributeName;

			ATTRIBUTED_DECLARATIONS(World, Attributed)
		};
	}
}
