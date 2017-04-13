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

		const char AttributedReaction::TypeSeparator = '.';

		AttributedReaction::AttributedReaction(const std::string& name) :
			Reaction(name)
		{
			AddInternalAttribute("Subtype", "", 0);
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
					Vector<std::string> auxiliaryAttributes;
					AuxiliaryAttributes(auxiliaryAttributes);
					for (const auto& attribute : auxiliaryAttributes)
					{
						attribute;
						//(*this)[attribute] = message[attribute];
					}
					Update(message.GetWorld()->GetWorldState());
				}
			}
		}

		bool AttributedReaction::MatchSubtype(const std::string& subtype) const
		{
			const Datum& subtypes = (*this)["Subtype"];;
			for (std::uint32_t index = 0; index < subtypes.Size(); ++index)
			{
				const std::string& reactionSubtype = (*this)["Subtype"].Get<std::string>(index);
				if (reactionSubtype == subtype.substr(0, reactionSubtype.length()))
				{
					if (subtype.length() > reactionSubtype.length() && !(subtype[reactionSubtype.length()] == TypeSeparator))
					{
						continue;
					}
					return true;
				}
			}
			return false;
		}

		void AttributedReaction::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("Subtype");
		}

		REACTION_FACTORY_DEFINITIONS(AttributedReaction);
	}
}
