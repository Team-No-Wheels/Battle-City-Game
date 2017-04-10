#include "Pch.h"
#include "BarSubscriber.h"
#include "Event.h"
#include "EventQueue.h"
#include "FooSubscriber.h"
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

		TEST_CLASS_INITIALIZE(InitializeClass)
		{
			mHelper.BeginClass();
			Event<Foo> foo(mHelper.GetRandomUInt32());
			Event<Bar> bar(mHelper.GetRandomUInt32());
		}

		TEST_METHOD_INITIALIZE(Setup)
		{
			Event<Foo>::UnsubscribeAll();
			Event<Bar>::UnsubscribeAll();
			mHelper.Setup();
		}

		TEST_METHOD_CLEANUP(Teardown)
		{
			Event<Foo>::UnsubscribeAll();
			Event<Bar>::UnsubscribeAll();
			mHelper.Teardown();
		}

		TEST_CLASS_CLEANUP(CleanupClass)
		{
			mHelper.EndClass();
		}

		static TestClassHelper mHelper;
	};

	TestClassHelper EventTest::mHelper;
}
