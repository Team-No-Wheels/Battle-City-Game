#include "World.h"
#include "Sector.h"
#include "WorldState.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(World)

		const std::string World::SectorsAttributeName = "Sectors";

		World::World(const std::string& name) :
			mSectors(&AddDatumAttribute(SectorsAttributeName)), mName(name)
		{
			mSectors->SetType(Datum::DatumType::Scope);
			AddExternalAttribute("mName", &mName, 1);
		}

		std::string World::Name() const
		{
			return mName;
		}

		void World::SetName(const std::string& name)
		{
			mName = name;
		}

		Datum& World::Sectors()
		{
			return (*mSectors);
		}

		Sector& World::CreateSector(const std::string& name)
		{
			Sector* sector = new Sector(name);
			mSectors->PushBack(sector);
			return (*sector);
		}

		void World::AdoptSector(Sector& sector)
		{
			Adopt(sector, SectorsAttributeName);
		}

		void World::Update(WorldState& worldState)
		{
			worldState.mWorld = this;
			for (std::uint32_t index = 0; index < mSectors->Size(); ++index)
			{
				Sector* sector = static_cast<Sector*>(mSectors->Get<Scope*>(index));
				sector->Update(worldState);
			}
		}

		void World::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack(SectorsAttributeName);
			prescribedAttributeNames.PushBack("mName");
		}
	}
}
