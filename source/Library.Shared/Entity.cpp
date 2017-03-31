#include "Entity.h"

#include <cassert>
#include "Action.h"
#include "Sector.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(Entity)

		const std::string Entity::ActionsAttributeName = "Actions";

		Entity::Entity(const std::string& name) :
			mActions(&AddDatumAttribute(ActionsAttributeName)), mName(name)
		{
			mActions->SetType(Datum::DatumType::Scope);
			AddExternalAttribute("mName", &mName, 1);
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
			return *(static_cast<Sector*>(GetParent()));
		}

		void Entity::AdoptAction(Action& action)
		{
			Adopt(action, ActionsAttributeName);
		}

		void Entity::Update(WorldState& worldState)
		{
			worldState.mEntity = this;
			for (std::uint32_t index = 0; index < mActions->Size(); ++index)
			{
				Action* action = static_cast<Action*>(mActions->Get<Scope*>(index));
				action->Update(worldState);
			};
		}

		void Entity::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack(ActionsAttributeName);
			prescribedAttributeNames.PushBack("mName");
		}
	}
}
