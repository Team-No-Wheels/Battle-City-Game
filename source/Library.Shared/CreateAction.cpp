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

		void CreateAction::Update(WorldState& worldState)
		{
			assert(worldState.mWorld != nullptr);

			worldState.mAction = this;
			// TODO: implement action
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
