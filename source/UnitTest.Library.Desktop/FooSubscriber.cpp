#include "Pch.h"
#include <cassert>
#include "FooSubscriber.h"
#include "Event.h"

namespace UnitTestLibraryDesktop
{
	using namespace AnonymousEngine::Core;

	FooSubscriber::FooSubscriber() :
		mIsNotified(false), mData(nullptr)
	{
	}

	void FooSubscriber::Notify(EventPublisher& publisher)
	{
		mIsNotified = true;
		assert(publisher.Is(Event<Foo>::TypeIdClass()));
		mData = const_cast<Foo*>(&static_cast<Event<Foo>&>(publisher).Message());
	}

	bool FooSubscriber::IsNotified() const
	{
		return mIsNotified;
	}

	const Foo* FooSubscriber::EventData() const
	{
		return mData;
	}
}
