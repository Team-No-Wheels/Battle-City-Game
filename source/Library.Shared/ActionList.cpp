#include "ActionList.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(ActionList)

		ActionList::ActionList(const std::string& name) :
			Action(name), mActions(nullptr)
		{
			AddDatumAttribute(ActionsAttributeName, mActions);
			mActions->SetType(Datum::DatumType::Scope);
		}

		Datum& ActionList::Actions()
		{
			return (*mActions);
		}

		Action& ActionList::CreateAction(const std::string& name, const std::string& className)
		{
			Action* action = Factory<Action>::Create(className);
			action->SetName(name);
			AdoptAction(*action);
			return (*action);
		}

		void ActionList::AdoptAction(Action& action)
		{
			Adopt(action, ActionsAttributeName);
		}

		void ActionList::Update(WorldState& worldState)
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

		void ActionList::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("Actions");
		}

		ACTION_FACTORY_DEFINITIONS(ActionList)
	}
}
