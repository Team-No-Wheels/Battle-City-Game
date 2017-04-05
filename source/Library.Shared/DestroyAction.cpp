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
			AddExternalAttribute("InstanceName", &mInstanceName, 1);
		}

		void DestroyAction::Update(WorldState& worldState)
		{
			assert(worldState.mWorld != nullptr);
			worldState.mAction = this;

			Datum* foundDatum = nullptr;
			Scope* searchScope = GetParent();
			while(searchScope != nullptr)
			{
				foundDatum = searchScope->Search(ActionsAttributeName, &searchScope);
				if (foundDatum != nullptr)
				{
					for (std::uint32_t index = 0; index < foundDatum->Size(); ++index)
					{
						assert(foundDatum->Get<Scope>(index).Is(Action::TypeIdClass()));
						Action& action = static_cast<Action&>(foundDatum->Get<Scope>(index));
						if (action.Name() == mInstanceName)
						{
							worldState.mWorld->MarkForDelete(action);
							foundDatum = nullptr;
							break;
						}
					}
				}

				if (foundDatum == nullptr)
				{
					break;
				}
				searchScope = searchScope->GetParent();
			}
			
			worldState.mAction = nullptr;
			assert(worldState.mWorld != nullptr);
		}

		void DestroyAction::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("InstanceName");
		}

		ACTION_FACTORY_DEFINITIONS(DestroyAction)
	}
}
