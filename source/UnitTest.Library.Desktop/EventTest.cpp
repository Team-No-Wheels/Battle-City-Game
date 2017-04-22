#include "Pch.h"
#include "BarSubscriber.h"
#include "Event.h"
#include "EventMessageAttributed.h"
#include "EventQueue.h"
#include "FooSubscriber.h"
#include "MultiThreadedSubscriber.h"
#include "TestClassHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	using namespace AnonymousEngine::Core;
	using namespace std::chrono;

	TEST_CLASS(EventTest)
	{
	public:
		TEST_METHOD(TestDirectDelivery)
		{
			EventQueue queue;
			FooSubscriber fooSubscriber;
			Foo fooData (mHelper.GetRandomUInt32());
			auto fooEvent = std::make_shared<Event<Foo>>(fooData);
			Event<Foo>::Subscribe(fooSubscriber);

			BarSubscriber barSubscriber;
			Bar barData(mHelper.GetRandomUInt32());
			auto barEvent = std::make_shared<Event<Bar>>(barData);
			Event<Bar>::Subscribe(barSubscriber);

			Assert::IsFalse(fooSubscriber.IsNotified());
			Assert::IsNull(fooSubscriber.EventData());
			Assert::IsFalse(barSubscriber.IsNotified());
			Assert::IsNull(barSubscriber.EventData());

			fooEvent->Deliver();
			Assert::IsTrue(fooSubscriber.IsNotified());
			Assert::IsTrue(fooData == *fooSubscriber.EventData());
			Assert::IsFalse(barSubscriber.IsNotified());
			Assert::IsNull(barSubscriber.EventData());

			barEvent->Deliver();
			Assert::IsTrue(barSubscriber.IsNotified());
			Assert::IsTrue(barData == *barSubscriber.EventData());
			Assert::IsTrue(barSubscriber.IsNotified());
			Assert::IsTrue(barData == *barSubscriber.EventData());
		}

		TEST_METHOD(TestDelayedDelivery)
		{
			EventQueue queue;
			GameTime time;
			std::uint32_t fooTime = (mHelper.GetRandomUInt32() % 1000) + 100;
			std::uint32_t barTime = fooTime / 2;

			FooSubscriber fooSubscriber;
			Foo fooData(mHelper.GetRandomUInt32());
			auto fooEvent = std::make_shared<Event<Foo>>(fooData);
			queue.Enqueue(fooEvent, time, fooTime);
			Event<Foo>::Subscribe(fooSubscriber);

			BarSubscriber barSubscriber;
			Bar barData(mHelper.GetRandomUInt32());
			auto barEvent = std::make_shared<Event<Bar>>(barData);
			Event<Bar>::Subscribe(barSubscriber);
			time.SetCurrentTime(time.CurrentTime() + milliseconds(1U));
			queue.Enqueue(barEvent, time, barTime);

			Bar barData2(mHelper.GetRandomUInt32());
			auto barEvent2 = std::make_shared<Event<Bar>>(barData2);
			time.SetCurrentTime(time.CurrentTime());
			queue.Enqueue(barEvent2, time, fooTime + 10);

			Assert::IsFalse(fooSubscriber.IsNotified());
			Assert::IsNull(fooSubscriber.EventData());
			Assert::IsFalse(barSubscriber.IsNotified());
			Assert::IsNull(barSubscriber.EventData());

			time.SetCurrentTime(time.CurrentTime() + milliseconds(barTime - 2));
			queue.Update(time);
			Assert::IsFalse(fooSubscriber.IsNotified());
			Assert::IsNull(fooSubscriber.EventData());
			Assert::IsFalse(barSubscriber.IsNotified());
			Assert::IsNull(barSubscriber.EventData());

			time.SetCurrentTime(time.CurrentTime() + milliseconds(2));
			queue.Update(time);
			Assert::IsFalse(fooSubscriber.IsNotified());
			Assert::IsNull(fooSubscriber.EventData());
			Assert::IsTrue(barSubscriber.IsNotified());
			Assert::IsTrue(barData == *barSubscriber.EventData());

			time.SetCurrentTime(time.CurrentTime() + milliseconds(fooTime - barTime + 4));
			queue.Update(time);
			Assert::IsTrue(fooSubscriber.IsNotified());
			Assert::IsTrue(fooData == *fooSubscriber.EventData());
			Assert::IsTrue(barSubscriber.IsNotified());
			Assert::IsTrue(barData == *barSubscriber.EventData());

			Assert::IsFalse(barData2 == *barSubscriber.EventData());
			time.SetCurrentTime(time.CurrentTime() + milliseconds(fooTime + 10));
			queue.Update(time);
			Assert::IsTrue(barData2 == *barSubscriber.EventData());
		}

		TEST_METHOD(TestEventQueueClearAndConstMethods)
		{
			EventQueue queue;
			GameTime time;
			std::uint32_t fooTime = (mHelper.GetRandomUInt32() % 1000) + 100;

			FooSubscriber fooSubscriber;
			Foo fooData(mHelper.GetRandomUInt32());
			auto fooEvent = std::make_shared<Event<Foo>>(fooData);

			Assert::IsTrue(queue.IsEmpty());
			Assert::AreEqual(0U, queue.Size());
			queue.Enqueue(fooEvent, time, fooTime);
			Assert::IsFalse(queue.IsEmpty());
			Event<Foo>::Subscribe(fooSubscriber);

			Assert::AreEqual(1U, queue.Size());
			Assert::IsFalse(queue.IsEmpty());
			Assert::IsFalse(fooSubscriber.IsNotified());
			queue.Send(fooEvent);
			Assert::IsTrue(fooSubscriber.IsNotified());
			queue.Clear();
			Assert::IsTrue(queue.IsEmpty());
			Assert::AreEqual(0U, queue.Size());
		}

		TEST_METHOD(TestMultiThreadedNotifyEnqueEvents)
		{
			EventQueue queue;
			GameTime time;
			const std::uint32_t barTime = (mHelper.GetRandomUInt32() % 100) + 10;
			const std::uint32_t fooTime = barTime + 10;

			FooSubscriber fooSubscriber;
			EnqueueFooSubscriberEvents(fooSubscriber, queue, time, fooTime);

			// Create subscribers
			const std::uint32_t subscriberCount = 100;
			Vector<std::unique_ptr<MultiThreadedSubscriber>> subscribers;
			CreateSubscribers(queue, subscribers, MultiThreadedSubscriber::TestType::Enqueue, subscriberCount);

			// Create events
			const std::uint32_t eventCount = 200;
			EnqueueTestEvents(queue, eventCount, time, barTime);

			time_point<high_resolution_clock> startPoint = time.CurrentTime();

			time.SetCurrentTime(startPoint + milliseconds(1U));
			AssertNoEventsDelivered(queue, fooSubscriber, subscribers, time);

			time.SetCurrentTime(startPoint + milliseconds(barTime));
			AssertOnlyBatchEventsAreDelivered(queue, fooSubscriber, subscribers, time, [&eventCount] (std::uint32_t count)
			{
				return eventCount == count;
			});

			time.SetCurrentTime(startPoint + milliseconds(fooTime));
			AssertAllEventsAreDelivered(queue, fooSubscriber, subscribers, time, [&eventCount](std::uint32_t count)
			{
				return eventCount == count;
			});
		}

		TEST_METHOD(TestMultiThreadedNotifySubscribeEvents)
		{
			EventQueue queue;
			GameTime time;
			const std::uint32_t barTime = (mHelper.GetRandomUInt32() % 100) + 10;
			const std::uint32_t fooTime = barTime + 10;

			FooSubscriber fooSubscriber;
			EnqueueFooSubscriberEvents(fooSubscriber, queue, time, fooTime);

			// Create subscribers
			const std::uint32_t subscriberCount = 100;
			Vector<std::unique_ptr<MultiThreadedSubscriber>> subscribers;
			CreateSubscribers(queue, subscribers, MultiThreadedSubscriber::TestType::Subscribe, subscriberCount);

			// Create events
			const std::uint32_t eventCount = 200;
			EnqueueTestEvents(queue, eventCount, time, barTime);

			time_point<high_resolution_clock> startPoint = time.CurrentTime();

			time.SetCurrentTime(startPoint + milliseconds(1U));
			AssertNoEventsDelivered(queue, fooSubscriber, subscribers, time);

			time.SetCurrentTime(startPoint + milliseconds(barTime));
			AssertOnlyBatchEventsAreDelivered(queue, fooSubscriber, subscribers, time, [&eventCount](std::uint32_t count)
			{
				return eventCount < count;
			});

			time.SetCurrentTime(startPoint + milliseconds(fooTime));
			AssertAllEventsAreDelivered(queue, fooSubscriber, subscribers, time, [&eventCount](std::uint32_t count)
			{
				return eventCount < count;
			});
		}

		TEST_METHOD(TestMultiThreadedNotifyUnsubscribeEvents)
		{
			EventQueue queue;
			GameTime time;
			const std::uint32_t barTime = (mHelper.GetRandomUInt32() % 100) + 10;
			const std::uint32_t fooTime = barTime + 10;

			FooSubscriber fooSubscriber;
			EnqueueFooSubscriberEvents(fooSubscriber, queue, time, fooTime);

			// Create subscribers
			const std::uint32_t subscriberCount = 100;
			Vector<std::unique_ptr<MultiThreadedSubscriber>> subscribers;
			CreateSubscribers(queue, subscribers, MultiThreadedSubscriber::TestType::Unsubscribe, subscriberCount);

			// Create events
			const std::uint32_t eventCount = 200;
			EnqueueTestEvents(queue, eventCount, time, barTime);

			time_point<high_resolution_clock> startPoint = time.CurrentTime();

			time.SetCurrentTime(startPoint + milliseconds(1U));
			AssertNoEventsDelivered(queue, fooSubscriber, subscribers, time);

			time.SetCurrentTime(startPoint + milliseconds(barTime));
			AssertOnlyBatchEventsAreDelivered(queue, fooSubscriber, subscribers, time, [&eventCount](std::uint32_t count)
			{
				return eventCount > count;
			});

			time.SetCurrentTime(startPoint + milliseconds(fooTime));
			AssertAllEventsAreDelivered(queue, fooSubscriber, subscribers, time, [&eventCount](std::uint32_t count)
			{
				return eventCount > count;
			});
		}

		TEST_METHOD(TestMultiThreadedNotifyUnsubscribeAll)
		{
			EventQueue queue;
			GameTime time;
			const std::uint32_t barTime = (mHelper.GetRandomUInt32() % 100) + 10;
			const std::uint32_t fooTime = barTime + 10;

			FooSubscriber fooSubscriber;
			EnqueueFooSubscriberEvents(fooSubscriber, queue, time, fooTime);

			// Create subscribers
			const std::uint32_t subscriberCount = 100;
			Vector<std::unique_ptr<MultiThreadedSubscriber>> subscribers;
			CreateSubscribers(queue, subscribers, MultiThreadedSubscriber::TestType::UnsubscribeAll, subscriberCount);

			// Create events
			const std::uint32_t eventCount = 200;
			EnqueueTestEvents(queue, eventCount, time, barTime);

			time_point<high_resolution_clock> startPoint = time.CurrentTime();

			time.SetCurrentTime(startPoint + milliseconds(1U));
			AssertNoEventsDelivered(queue, fooSubscriber, subscribers, time);

			time.SetCurrentTime(startPoint + milliseconds(barTime));
			AssertOnlyBatchEventsAreDelivered(queue, fooSubscriber, subscribers, time, [&eventCount](std::uint32_t count)
			{
				return eventCount > count;
			});

			time.SetCurrentTime(startPoint + milliseconds(fooTime));
			AssertAllEventsAreDelivered(queue, fooSubscriber, subscribers, time, [&eventCount](std::uint32_t count)
			{
				return eventCount > count;
			});
		}

		TEST_METHOD(TestMultiThreadedNotifyClearQueue)
		{
			EventQueue queue;
			GameTime time;
			const std::uint32_t barTime = (mHelper.GetRandomUInt32() % 100) + 10;
			const std::uint32_t fooTime = barTime + 10;

			FooSubscriber fooSubscriber;
			EnqueueFooSubscriberEvents(fooSubscriber, queue, time, fooTime);

			// Create subscribers
			const std::uint32_t subscriberCount = 100;
			Vector<std::unique_ptr<MultiThreadedSubscriber>> subscribers;
			CreateSubscribers(queue, subscribers, MultiThreadedSubscriber::TestType::Clear, subscriberCount);

			// Create events
			const std::uint32_t eventCount = 200;
			EnqueueTestEvents(queue, eventCount, time, barTime);

			time_point<high_resolution_clock> startPoint = time.CurrentTime();

			time.SetCurrentTime(startPoint + milliseconds(1U));
			AssertNoEventsDelivered(queue, fooSubscriber, subscribers, time);

			time.SetCurrentTime(startPoint + milliseconds(barTime));
			AssertOnlyBatchEventsAreDelivered(queue, fooSubscriber, subscribers, time, [&eventCount](std::uint32_t count)
			{
				return eventCount == count;
			});

			time.SetCurrentTime(startPoint + milliseconds(fooTime));
			Assert::IsFalse(fooSubscriber.IsNotified());
			Assert::IsNull(fooSubscriber.EventData());
		}

		TEST_METHOD(TestMultiThreadedNotifyException)
		{
			EventQueue queue;
			GameTime time;
			const std::uint32_t barTime = (mHelper.GetRandomUInt32() % 100) + 10;
			const std::uint32_t fooTime = barTime + 10;

			FooSubscriber fooSubscriber;
			EnqueueFooSubscriberEvents(fooSubscriber, queue, time, fooTime);

			// Create subscribers
			const std::uint32_t subscriberCount = 100;
			Vector<std::unique_ptr<MultiThreadedSubscriber>> subscribers;
			CreateSubscribers(queue, subscribers, MultiThreadedSubscriber::TestType::Exception, subscriberCount);

			// Create events
			const std::uint32_t eventCount = 200;
			EnqueueTestEvents(queue, eventCount, time, barTime);

			time_point<high_resolution_clock> startPoint = time.CurrentTime();

			time.SetCurrentTime(startPoint + milliseconds(1U));
			AssertNoEventsDelivered(queue, fooSubscriber, subscribers, time);

			time.SetCurrentTime(startPoint + milliseconds(barTime));
			Assert::IsFalse(fooSubscriber.IsNotified());
			Assert::IsNull(fooSubscriber.EventData());
			Assert::ExpectException<std::exception>([&queue, &time]()
			{
				queue.Update(time);
			});

			time.SetCurrentTime(startPoint + milliseconds(fooTime));
			Assert::IsFalse(fooSubscriber.IsNotified());
			Assert::IsNull(fooSubscriber.EventData());
		}
		TEST_CLASS_INITIALIZE(InitializeClass)
		{
			mHelper.BeginClass();
			Event<Foo> foo(mHelper.GetRandomUInt32());
			Event<Bar> bar(mHelper.GetRandomUInt32());
			Containers::EventMessageAttributed message;
			Event<Containers::EventMessageAttributed> event(message);
		}

		TEST_METHOD_INITIALIZE(Setup)
		{
			Event<Foo>::UnsubscribeAll();
			Event<Bar>::UnsubscribeAll();
			Event<Containers::EventMessageAttributed>::UnsubscribeAll();
			mHelper.Setup();
		}

		TEST_METHOD_CLEANUP(Teardown)
		{
			Event<Foo>::UnsubscribeAll();
			Event<Bar>::UnsubscribeAll();
			Event<Containers::EventMessageAttributed>::UnsubscribeAll();
			mHelper.Teardown();
		}

		TEST_CLASS_CLEANUP(CleanupClass)
		{
			mHelper.EndClass();
		}

	private:
		static void EnqueueFooSubscriberEvents(FooSubscriber& subscriber, EventQueue& queue, const GameTime& time, const uint32_t delay)
		{
			Foo fooData(mHelper.GetRandomUInt32());
			auto fooEvent = std::make_shared<Event<Foo>>(fooData);
			Event<Foo>::Subscribe(subscriber);
			queue.Enqueue(fooEvent, time, delay);
		}

		static void CreateSubscribers(EventQueue& queue, Vector<std::unique_ptr<MultiThreadedSubscriber>>& subscribers, MultiThreadedSubscriber::TestType type, const std::uint32_t subscriberCount)
		{
			subscribers.Reserve(subscriberCount);
			for (std::uint32_t i = 0; i < subscriberCount; ++i)
			{
				subscribers.PushBack(std::make_unique<MultiThreadedSubscriber>(queue, type));
				Event<Containers::EventMessageAttributed>::Subscribe(*subscribers[i]);
			}
		}

		static void EnqueueTestEvents(EventQueue& queue, std::uint32_t eventCount, const GameTime& time, uint32_t delay)
		{
			for (std::uint32_t i = 0; i < eventCount; ++i)
			{
				Containers::EventMessageAttributed message;
				auto barEvent = std::make_shared<Event<Containers::EventMessageAttributed>>(message);
				queue.Enqueue(barEvent, time, delay);
			}
		}

		static void AssertNoEventsDelivered(EventQueue& queue, FooSubscriber& fooSubscriber, const Vector<std::unique_ptr<MultiThreadedSubscriber>>& subscribers, GameTime& time)
		{
			queue.Update(time);
			Assert::IsFalse(fooSubscriber.IsNotified());
			Assert::IsNull(fooSubscriber.EventData());
			for (std::uint32_t i = 0; i < subscribers.Size(); ++i)
			{
				Assert::AreEqual(0U, subscribers[i]->NotifiedCount());
			}
		}

		static void AssertOnlyBatchEventsAreDelivered(EventQueue& queue, FooSubscriber& fooSubscriber, const Vector<std::unique_ptr<MultiThreadedSubscriber>>& subscribers, GameTime& time,
			std::function<bool(std::uint32_t)> matchPredicate)
		{
			queue.Update(time);
			Assert::IsFalse(fooSubscriber.IsNotified());
			Assert::IsNull(fooSubscriber.EventData());
			for (std::uint32_t i = 0; i < subscribers.Size(); ++i)
			{
				Assert::IsTrue(matchPredicate(subscribers[i]->NotifiedCount()));
			}
		}

		static void AssertAllEventsAreDelivered(EventQueue& queue, FooSubscriber& fooSubscriber, const Vector<std::unique_ptr<MultiThreadedSubscriber>>& subscribers, GameTime& time,
			std::function<bool(std::uint32_t)> matchPredicate)
		{
			queue.Update(time);
			Assert::IsTrue(fooSubscriber.IsNotified());
			Assert::IsNotNull(fooSubscriber.EventData());
			for (std::uint32_t i = 0; i < subscribers.Size(); ++i)
			{
				Assert::IsTrue(matchPredicate(subscribers[i]->NotifiedCount()));
			}
		}

		static TestClassHelper mHelper;
	};

	TestClassHelper EventTest::mHelper;
}
