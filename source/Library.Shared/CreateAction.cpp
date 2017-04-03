#include "CreateAction.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(CreateAction)

		CreateAction::CreateAction(const std::string& name) :
			Action(name)
		{
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
			GetParent()->Adopt(*(Factory<Action>::Create(mClassName)), ActionsAttributeName);
			worldState.mAction = nullptr;
			assert(worldState.mWorld != nullptr);
		}

		void CreateAction::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		}

		ACTION_FACTORY_DEFINITIONS(CreateAction)
	}
}
