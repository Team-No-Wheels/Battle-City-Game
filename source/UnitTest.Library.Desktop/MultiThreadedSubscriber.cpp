#include "Pch.h"
#include <cassert>
#include "Event.h"
#include "EventMessageAttributed.h"
#include "EventQueue.h"
#include "MultiThreadedSubscriber.h"

namespace UnitTestLibraryDesktop
{
	using namespace AnonymousEngine::Core;

	MultiThreadedSubscriber::HandlerType MultiThreadedSubscriber::TestHandlers = {
		{TestType::None, [] (MultiThreadedSubscriber&) {}},
		{TestType::Enqueue, EnqueueHandler},
		{TestType::Clear, ClearHandler},
		{TestType::Subscribe, SubscribeHandler},
		{TestType::Unsubscribe, UnsubscribeHandler},
		{TestType::UnsubscribeAll, UnsubscribeAllHandler},
		{TestType::Exception, ExceptionHandler}
	};

	MultiThreadedSubscriber* MultiThreadedSubscriber::Subscriber = nullptr;

	MultiThreadedSubscriber::MultiThreadedSubscriber(EventQueue& eventQueue, TestType testType) :
		mEventQueue(eventQueue), mTestType(testType), mNotifiedCount(0)
	{
	}

	void MultiThreadedSubscriber::Notify(EventPublisher& publisher)
	{
		publisher;
		assert(publisher.Is(Event<AnonymousEngine::Containers::EventMessageAttributed>::TypeIdClass()));
		{
			std::lock_guard<std::mutex> lock(mMutex);
			++mNotifiedCount;
		}
		TestHandlers[mTestType](*this);
	}

	std::uint32_t MultiThreadedSubscriber::NotifiedCount() const
	{
		return mNotifiedCount;
	}

	void MultiThreadedSubscriber::EnqueueHandler(MultiThreadedSubscriber& subscriber)
	{
		auto event = std::make_shared<Event<std::uint32_t>>(1);
		subscriber.mEventQueue.Enqueue(event, AnonymousEngine::GameTime(), 10);
	}

	void MultiThreadedSubscriber::ClearHandler(MultiThreadedSubscriber& subscriber)
	{
		subscriber.mEventQueue.Clear();
	}

	void MultiThreadedSubscriber::SubscribeHandler(MultiThreadedSubscriber& subscriber)
	{
		Event<AnonymousEngine::Containers::EventMessageAttributed>::Subscribe(subscriber);
	}

	void MultiThreadedSubscriber::UnsubscribeHandler(MultiThreadedSubscriber& subscriber)
	{
		Event<AnonymousEngine::Containers::EventMessageAttributed>::Unsubscribe(subscriber);
	}

	void MultiThreadedSubscriber::UnsubscribeAllHandler(MultiThreadedSubscriber&)
	{
		Event<AnonymousEngine::Containers::EventMessageAttributed>::UnsubscribeAll();
	}

	void MultiThreadedSubscriber::ExceptionHandler(MultiThreadedSubscriber&)
	{
		throw std::exception("Event exception");
	}
}
