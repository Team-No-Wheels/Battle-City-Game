#include "World.h"

#include <cassert>
#include "Action.h"
#include "Sector.h"
#include "WorldState.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(World)

		const std::string World::SectorsAttributeName = "Sectors";

		World::World(const std::string& name) :
			mName(name), mSectors(nullptr), mActions(nullptr)
		{
			AddExternalAttribute("Name", &mName, 1);
			AddDatumAttribute(SectorsAttributeName, mSectors);
			mSectors->SetType(Datum::DatumType::Scope);
			AddDatumAttribute(Action::ActionsAttributeName, mActions);
			mSectors->SetType(Datum::DatumType::Scope);
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
			AdoptSector(*sector);
			return (*sector);
		}

		void World::AdoptSector(Sector& sector)
		{
			Adopt(sector, SectorsAttributeName);
		}

		Datum& World::Actions()
		{
			return (*mActions);
		}

		void World::Update(WorldState& worldState)
		{
			assert(worldState.mWorld == nullptr);
			worldState.mWorld = this;

			// update actions
			for (std::uint32_t index = 0; index < Actions().Size(); ++index)
			{
				Action* action = static_cast<Action*>(&mActions->Get<Scope>(index));
				action->Update(worldState);
			}

			// update sectors
			for (std::uint32_t index = 0; index < Sectors().Size(); ++index)
			{
				Sector* sector = static_cast<Sector*>(&mSectors->Get<Scope>(index));
				sector->Update(worldState);
			}

			// garbage collection
			for (auto attributed : mGarbageQueue)
			{
				attributed->Orphan();
				delete attributed;
			}
			mGarbageQueue.Clear();
			worldState.mWorld = nullptr;
		}

		void World::MarkForDelete(Attributed& attributed)
		{
			mGarbageQueue.PushBack(&attributed);
		}

		void World::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("Name");
			prescribedAttributeNames.PushBack("Sectors");
			prescribedAttributeNames.PushBack("Actions");
		}
	}
}
