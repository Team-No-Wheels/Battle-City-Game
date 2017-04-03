#include "DestroyAction.h"
#include "World.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(DestroyAction)

		DestroyAction::DestroyAction(const std::string& name) :
			Action(name)
		{
		}

		void DestroyAction::Update(WorldState& worldState)
		{
			assert(worldState.mWorld != nullptr);
			worldState.mAction = this;
			worldState.mWorld->MarkForDelete(*this);
			worldState.mAction = nullptr;
			assert(worldState.mWorld != nullptr);
		}

		void DestroyAction::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		}

		ACTION_FACTORY_DEFINITIONS(DestroyAction)
	}
}
