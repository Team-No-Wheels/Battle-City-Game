#pragma once

#include "EventSubscriber.h"
#include "Bar.h"

namespace UnitTestLibraryDesktop
{
	class BarSubscriber final : public AnonymousEngine::Core::EventSubscriber
	{
	public:

		BarSubscriber();
		~BarSubscriber() = default;
		void Notify(AnonymousEngine::Core::EventPublisher& publisher) override;
		bool IsNotified() const;
		const Bar* EventData() const;
	private:
		bool mIsNotified;
		Bar* mData;
	};
}
