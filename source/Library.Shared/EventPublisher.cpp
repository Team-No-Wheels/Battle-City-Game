#include "EventPublisher.h"
#include "EventSubscriber.h"

namespace AnonymousEngine
{
	namespace Core
	{
		RTTI_DEFINITIONS(EventPublisher)

		EventPublisher::EventPublisher(Vector<class EventSubscriber*>* subscriberList) :
			mSubscribers(subscriberList)
		{
		}

		void EventPublisher::Deliver()
		{
			for (auto& subscriber : *mSubscribers)
			{
				subscriber->Notify(*this);
			}
		}
	}
}
