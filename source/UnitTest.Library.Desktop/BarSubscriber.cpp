#include "Pch.h"
#include <cassert>
#include "BarSubscriber.h"
#include "Event.h"

namespace UnitTestLibraryDesktop
{
	using namespace AnonymousEngine::Core;

	BarSubscriber::BarSubscriber() :
		mIsNotified(false), mData(nullptr)
	{
	}

	void BarSubscriber::Notify(EventPublisher& publisher)
	{
		assert(publisher.Is(Event<Bar>::TypeIdClass()));
		mIsNotified = true;
		mData = const_cast<Bar*>(&static_cast<Event<Bar>&>(publisher).Message());
	}

	bool BarSubscriber::IsNotified() const
	{
		return mIsNotified;
	}

	const Bar* BarSubscriber::EventData() const
	{
		return mData;
	}
}
