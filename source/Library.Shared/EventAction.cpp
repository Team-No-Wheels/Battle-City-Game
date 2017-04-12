#include "EventAction.h"
#include "Event.h"
#include "EventMessageAttributed.h"
#include "World.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		using namespace AnonymousEngine::Core;

		EventAction::EventAction(const std::string& name) :
			Action(name), mDelay(0)
		{
			AddExternalAttribute("Subtype", &mSubtype, 1);
			AddExternalAttribute("Delay", &mDelay, 1);
		}

		void EventAction::Update(WorldState& worldState)
		{
			EventMessageAttributed message;
			message.SetWorld(*worldState.mWorld);
			message.SetSubtype(mSubtype);

			Vector<std::string> auxiliaryAttributes;
			AuxiliaryAttributes(auxiliaryAttributes);
			for (const auto& attribute : auxiliaryAttributes)
			{
				message[attribute] = (*this)[attribute];
			}
			worldState.mWorld->EventQueue().Enqueue(std::make_shared<Event<EventMessageAttributed>>(message), worldState.mGameTime, mDelay);
		}

		void EventAction::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("Subtype");
			prescribedAttributeNames.PushBack("Delay");
		}

		ACTION_FACTORY_DEFINITIONS(EventAction)
	}
}
