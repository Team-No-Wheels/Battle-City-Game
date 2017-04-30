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
			mName(name), mSectors(nullptr), mActions(nullptr), mWorldState(WorldState())
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

		void World::InitializeWorld()
		{
			mWorldState.mCurrentLevel = 0;
		}

		void World::LoadNextLevel()
		{
			mWorldState.mCurrentLevel++;
		}

		Datum& World::Sectors() const
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

		Datum& World::Actions() const
		{
			return (*mActions);
		}

		void World::Update()
		{
			assert(mWorldState.mWorld == nullptr);
			mWorldState.mWorld = this;

			// Update event queue
			mEventQueue.Update(mWorldState.mGameTime);

			// update actions
			for (std::uint32_t index = 0; index < Actions().Size(); ++index)
			{
				Action* action = static_cast<Action*>(&mActions->Get<Scope>(index));
				action->Update(mWorldState);
			}

			// update sectors
			for (std::uint32_t index = 0; index < Sectors().Size(); ++index)
			{
				Sector* sector = static_cast<Sector*>(&mSectors->Get<Scope>(index));
				sector->Update(mWorldState);
			}

			// garbage collection
			for (auto attributed : mGarbageQueue)
			{
				attributed->Orphan();
				delete attributed;
			}
			mGarbageQueue.Clear();
			mWorldState.mWorld = nullptr;
		}

		void World::MarkForDelete(Attributed& attributed)
		{
			std::lock_guard<std::mutex> lock(mGarbageQueueMutex);
			mGarbageQueue.PushBack(&attributed);
		}

		Core::EventQueue& World::EventQueue()
		{
			return mEventQueue;
		}

		WorldState& World::GetWorldState()
		{
			return mWorldState;
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
