#include "AttributedReaction.h"
#include "Event.h"
#include "EventPublisher.h"
#include "EventMessageAttributed.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		using namespace AnonymousEngine::Core;

		ATTRIBUTED_DEFINITIONS(AttributedReaction)

		AttributedReaction::AttributedReaction(const std::string& name) :
			Reaction(name), mEventArgs(new EventMessageAttributed())
		{
			AddExternalAttribute("Subtype", &mSubtype, 1);
			AddNestedScope("EventArgs", *mEventArgs);
		}

		void AttributedReaction::Notify(Core::EventPublisher& publisher)
		{
			if (publisher.Is(Event<EventMessageAttributed>::TypeIdClass()))
			{
				Event<EventMessageAttributed>& attributedEvent = static_cast<Event<EventMessageAttributed>&>(publisher);
				const EventMessageAttributed& message = attributedEvent.Message();
				*mEventArgs = message;
			}
		}

		void AttributedReaction::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("Subtype");
			prescribedAttributeNames.PushBack("EventArgs");
		}

		REACTION_FACTORY_DEFINITIONS(AttributedReaction);
	}
}
