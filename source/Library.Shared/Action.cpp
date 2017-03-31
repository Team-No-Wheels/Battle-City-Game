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
			AddExternalAttribute("Name", &mName, 1);
			AddDatumAttribute(ActionsAttributeName, mActions);
			mActions->SetType(Datum::DatumType::Scope);
		}

		std::string Action::Name() const
		{
			return mName;
		}

		void Action::SetName(const std::string& name)
		{
			mName = name;
		}

		Datum& Action::Actions()
		{
			return (*mActions);
		}

		Action& Action::CreateAction(const std::string& name, const std::string& className)
		{
			Action* action = Factory<Action>::Create(className);
			action->SetName(name);
			AdoptAction(*action);
			return (*action);
		}

		void Action::AdoptAction(Action& action)
		{
			Adopt(action, ActionsAttributeName);
		}

		void Action::Update(WorldState& worldState)
		{
			assert(worldState.mWorld != nullptr);

			worldState.mAction = this;
			for (std::uint32_t index = 0; index < mActions->Size(); ++index)
			{
				Action* action = static_cast<Action*>(&mActions->Get<Scope>(index));
				action->Update(worldState);
			};
			worldState.mAction = nullptr;

			assert(worldState.mWorld != nullptr);
		}

		void Action::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("Name");
			prescribedAttributeNames.PushBack("Actions");
		}
	}
}
