#include "Pch.h"
#include "BarSubscriber.h"
#include "Event.h"
#include "FooSubscriber.h"
#include "TestClassHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	using namespace AnonymousEngine::Core;

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

		TEST_CLASS_INITIALIZE(InitializeClass)
		{
			mHelper.BeginClass();
		}

		TEST_METHOD_INITIALIZE(Setup)
		{
			mHelper.Setup();
		}

		TEST_METHOD_CLEANUP(Teardown)
		{
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
