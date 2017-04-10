#pragma once

#include "EventSubscriber.h"
#include "Foo.h"

namespace UnitTestLibraryDesktop
{
	class FooSubscriber final : public AnonymousEngine::Core::EventSubscriber
	{
	public:
		FooSubscriber();
		~FooSubscriber() = default;
		void Notify(AnonymousEngine::Core::EventPublisher& publisher) override;
		bool IsNotified() const;
		const Foo* EventData() const;
	private:
		bool mIsNotified;
		Foo* mData;
	};
}
