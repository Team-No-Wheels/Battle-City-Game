#include "EventPublisher.h"
#include "EventSubscriber.h"
#include <future>

namespace AnonymousEngine
{
	namespace Core
	{
		RTTI_DEFINITIONS(EventPublisher)

		EventPublisher::EventPublisher(const Vector<class EventSubscriber*>& subscriberList, std::mutex& mutex) :
			mSubscribers(subscriberList), mListMutex(mutex)
		{
		}

		void EventPublisher::Deliver()
		{
			Vector<EventSubscriber*> tempList;
			{
				std::lock_guard<std::mutex> lock(mListMutex);
				tempList = mSubscribers;
			}
			
			Vector<std::future<void>> futures;
			for (auto& subscriber : tempList)
			{
				futures.PushBack(std::async([&subscriber, this]()
				{
					subscriber->Notify(*this);
				}));
			}
			for (auto& f : futures)
			{
				f.wait();
			}
			for (auto& f : futures)
			{
				f.get();
			}
		}
	}
}
