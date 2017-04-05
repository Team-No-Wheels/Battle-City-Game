#include "Sector.h"

#include <cassert>
#include "Action.h"
#include "Entity.h"
#include "World.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(Sector)

		const std::string Sector::EntitiesAttributeName = "Entities";

		Sector::Sector(const std::string& name) :
			mName(name), mEntities(nullptr)
		{
			AddExternalAttribute("Name", &mName, 1);
			AddDatumAttribute(EntitiesAttributeName, mEntities);
			mEntities->SetType(Datum::DatumType::Scope);
			AddDatumAttribute(Action::ActionsAttributeName, mActions);
			mEntities->SetType(Datum::DatumType::Scope);
		}

		std::string Sector::Name() const
		{
			return mName;
		}

		void Sector::SetName(const std::string& name)
		{
			mName = name;
		}

		World& Sector::GetWorld()
		{
			assert(GetParent()->Is(World::TypeIdClass()));
			return *(static_cast<World*>(GetParent()));
		}

		Datum& Sector::Entities()
		{
			return (*mEntities);
		}

		Entity& Sector::CreateEntity(const std::string& name, const std::string& className)
		{
			Entity* entity = Factory<Entity>::Create(className);
			entity->SetName(name);
			AdoptEntity(*entity);
			return (*entity);
		}

		void Sector::AdoptEntity(Entity& entity)
		{
			Adopt(entity, EntitiesAttributeName);
		}

		Datum& Sector::Actions()
		{
			return (*mActions);
		}

		void Sector::Update(WorldState& worldState)
		{
			assert(worldState.mWorld == static_cast<World*>(GetParent()));
			assert(worldState.mSector == nullptr);

			worldState.mSector = this;
			
			// update actions
			for (std::uint32_t index = 0; index < mActions->Size(); ++index)
			{
				Action* action = static_cast<Action*>(&mActions->Get<Scope>(index));
				action->Update(worldState);
			};
			
			// update entities
			for (std::uint32_t index = 0; index < mEntities->Size(); ++index)
			{
				Entity* entity = static_cast<Entity*>(&mEntities->Get<Scope>(index));
				entity->Update(worldState);
			};
			worldState.mSector = nullptr;

			assert(worldState.mWorld == static_cast<World*>(GetParent()));
		}

		void Sector::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("Name");
			prescribedAttributeNames.PushBack("Entities");
			prescribedAttributeNames.PushBack("Actions");
		}
	}
}
