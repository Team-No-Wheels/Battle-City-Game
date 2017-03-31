#include "Action.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(Action)

		ACTION_FACTORY_DEFINITIONS(Action)

		const std::string Action::ActionsAttributeName = "Actions";

		Action::Action(const std::string& name) :
			mName(name), mActions(nullptr)
		{
			mActions->SetType(Datum::DatumType::Scope);
			AddExternalAttribute("mName", &mName, 1);
			AddDatumAttribute(ActionsAttributeName, mActions);
		}

		std::string Action::Name() const
		{
			return mName;
		}

		void Action::SetName(const std::string& name)
		{
			mName = name;
		}

		void Action::AdoptAction(Action& action)
		{
			Adopt(action, ActionsAttributeName);
		}

		void Action::Update(WorldState& worldState)
		{
			worldState.mAction = this;
			for (std::uint32_t index = 0; index < mActions->Size(); ++index)
			{
				Action* action = static_cast<Action*>(mActions->Get<Scope*>(index));
				action->Update(worldState);
			};
		}

		void Action::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("mName");
			prescribedAttributeNames.PushBack(ActionsAttributeName);
		}
	}
}
