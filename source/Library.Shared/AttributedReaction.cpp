#include "AttributedReaction.h"
#include "Event.h"
#include "EventPublisher.h"
#include "EventMessageAttributed.h"
#include "World.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		using namespace AnonymousEngine::Core;

		ATTRIBUTED_DEFINITIONS(AttributedReaction)

		const std::string TypeSeparator = ".";

		AttributedReaction::AttributedReaction(const std::string& name) :
			Reaction(name), mEventArgs(new EventMessageAttributed())
		{
			AddExternalAttribute("Subtype", &mSubtype, 1);
		}

		void AttributedReaction::Notify(Core::EventPublisher& publisher)
		{
			if (publisher.Is(Event<EventMessageAttributed>::TypeIdClass()))
			{
				Event<EventMessageAttributed>& attributedEvent = static_cast<Event<EventMessageAttributed>&>(publisher);
				const EventMessageAttributed& message = attributedEvent.Message();
				assert(message.GetWorld() != nullptr);

				if (MatchSubtype(message.GetSubtype()))
				{
					*mEventArgs = message;
					Update(message.GetWorld()->GetWorldState());
				}
			}
		}

		bool AttributedReaction::MatchSubtype(const std::string& subtype) const
		{
			auto reactionTypeEnd = mSubtype.end();
			auto subtypeEnd = subtype.end();
			auto it = mSubtype.begin();
			auto subtypeIt = subtype.begin();
			for (; (it != reactionTypeEnd && subtypeIt != subtypeEnd); ++it, ++subtypeIt)
			{
				if (!(*it == *subtypeIt))
				{
					return false;
				}
			}
			return (subtypeIt == subtypeEnd || *(++subtypeIt) == TypeSeparator[0]);
		}

		void AttributedReaction::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("Subtype");
		}

		REACTION_FACTORY_DEFINITIONS(AttributedReaction);
	}
}
