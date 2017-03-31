#include "Sector.h"
#include "Entity.h"
#include "World.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(Sector)

		const std::string Sector::EntitiesAttributeName = "Entities";

		Sector::Sector(const std::string& name) :
			mEntities(&AddDatumAttribute(EntitiesAttributeName)), mName(name)
		{
			mEntities->SetType(Datum::DatumType::Scope);
			AddExternalAttribute("mName", &mName, 1);
		}

		std::string Sector::Name() const
		{
			return mName;
		}

		void Sector::SetName(const std::string& name)
		{
			mName = name;
		}

		Datum& Sector::Entities()
		{
			return (*mEntities);
		}

		Entity& Sector::CreateEntity(const std::string& name, const std::string& className)
		{
			className;
			Entity* entity = new Entity(name);
			mEntities->PushBack(entity);
			return (*entity);
		}

		void Sector::AdoptEntity(Entity& entity)
		{
			Adopt(entity, EntitiesAttributeName);
		}

		World& Sector::GetWorld()
		{
			return *(static_cast<World*>(GetParent()));
		}

		void Sector::Update(WorldState& worldState)
		{
			worldState.mSector = this;
			for (std::uint32_t index = 0; index < mEntities->Size(); ++index)
			{
				Entity* entity = static_cast<Entity*>(mEntities->Get<Scope*>(index));
				entity->Update(worldState);
			};
		}

		void Sector::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack(EntitiesAttributeName);
			prescribedAttributeNames.PushBack("mName");
		}
	}
}
