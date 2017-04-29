#include "Entity.h"

#include <cassert>
#include "Action.h"
#include "Sector.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(Entity)

		ENTITY_FACTORY_DEFINITIONS(Entity);

		const std::string Entity::ActionsAttributeName = "Actions";

		Entity::Entity(const std::string& name) :
			mName(name), mActions(nullptr), mPosition(glm::vec2(0,0))
		{
			AddExternalAttribute("Name", &mName, 1);
			AddDatumAttribute(ActionsAttributeName, mActions);
			mActions->SetType(Datum::DatumType::Scope);
		}

		std::string Entity::Name() const
		{
			return mName;
		}

		void Entity::SetName(const std::string& name)
		{
			mName = name;
		}

		Sector& Entity::GetSector()
		{
			assert(GetParent()->Is(Sector::TypeIdClass()));
			return *(static_cast<Sector*>(GetParent()));
		}

		Datum& Entity::Actions()
		{
			return (*mActions);
		}

		Action& Entity::CreateAction(const std::string& name, const std::string& className)
		{
			Action* action = Factory<Action>::Create(className);
			action->SetName(name);
			AdoptAction(*action);
			return (*action);
		}

		void Entity::AdoptAction(Action& action)
		{
			Adopt(action, ActionsAttributeName);
		}

		void Entity::Update(WorldState& worldState)
		{
			assert(worldState.mWorld != nullptr);
			assert(worldState.mSector == static_cast<Sector*>(GetParent()));
			assert(worldState.mEntity == nullptr);

			worldState.mEntity = this;
			for (std::uint32_t index = 0; index < Actions().Size(); ++index)
			{
				Action* action = static_cast<Action*>(&mActions->Get<Scope>(index));
				action->Update(worldState);
			};
			worldState.mEntity = nullptr;

			assert(worldState.mWorld != nullptr);
			assert(worldState.mSector == static_cast<Sector*>(GetParent()));
		}

		void Entity::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("Name");
			prescribedAttributeNames.PushBack("Actions");
		}
	
		void Entity::SetPosition(const glm::vec2& newPosition)
		{
			mPosition = newPosition;
		}

		glm::vec2& Entity::GetPosition()
		{
			return mPosition;
		}
	
	}
}
