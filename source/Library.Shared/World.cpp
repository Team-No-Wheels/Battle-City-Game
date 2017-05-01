#include "World.h"

#include <cassert>
#include "Action.h"
#include "Sector.h"
#include "WorldState.h"
#include "FrameManager.h"
#include "GameObject.h"
#include "SpriteSheet.h"

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
			Graphics::FrameManager& frameManager = static_cast<Graphics::FrameManager&>((*this)["FrameManager"].Get<Scope>());
			Datum& entities = static_cast<Sector&>(mSectors->Get<Scope>(mWorldState.GetCurrentLevel())).Entities();
			for (std::uint32_t index = 0; index < entities.Size(); ++index)
			{
				Core::GameObject& gameObj = static_cast<Core::GameObject&>(entities.Get<Scope>(index));
				
				const std::string& frameName = gameObj["SpriteName"].Get<std::string>();
				if (!frameName.empty())
				{
					Graphics::SpriteSheet* spriteSheet = new Graphics::SpriteSheet(gameObj);
					Graphics::Frame& frame = *frameManager.GetFrameEntity(frameName);
					spriteSheet->Init(frame.mFilePath);
					spriteSheet->SetFrame(frame);

					gameObj.GetSprite().SetTint(gameObj.GetTint());
				}
			}
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
			Sector* sector = static_cast<Sector*>(&mSectors->Get<Scope>(mWorldState.GetCurrentLevel()));
			sector->Update(mWorldState);

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
