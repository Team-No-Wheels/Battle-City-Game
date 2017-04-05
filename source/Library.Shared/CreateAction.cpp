#include "CreateAction.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(CreateAction)

		CreateAction::CreateAction(const std::string& name) :
			Action(name)
		{
			AddExternalAttribute("InstanceName", &mInstanceName, 1);
			AddExternalAttribute("ClassName", &mClassName, 1);
		}

		void CreateAction::SetClassName(const std::string& className)
		{
			mClassName = className;
		}

		const std::string& CreateAction::ClassName() const
		{
			return mClassName;
		}

		void CreateAction::Update(WorldState& worldState)
		{
			assert(worldState.mWorld != nullptr);
			worldState.mAction = this;
			Action* action = Factory<Action>::Create(mClassName);
			action->SetName(mInstanceName);
			GetParent()->Adopt(*action, ActionsAttributeName);
			worldState.mAction = nullptr;
			assert(worldState.mWorld != nullptr);
		}

		void CreateAction::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("InstanceName");
			prescribedAttributeNames.PushBack("ClassName");
		}

		ACTION_FACTORY_DEFINITIONS(CreateAction)
	}
}
