#pragma once

#include "EventPublisher.h"
#include "RTTI.h"

namespace AnonymousEngine
{
	namespace Core
	{
		template <typename T>
		class Event final : EventPublisher
		{
		public:
			Event() = default;
			~Event() = default;

			Event(Event& rhs);
			Event(Event&& rhs) noexcept;

			Event& operator=(Event& rhs);
			Event& operator=(Event&& rhs) noexcept;

			static void Subscribe(class EventSubscriber& subscriber);
			static void Unsubscribe(class EventSubscriber& subscriber);
			static void UnsubscribeAll();
			const T& Message();

		private:
			const T& mMessage;

			RTTI_DECLARATIONS(Event, EventPublisher);
		};
	}
}

#include "Event.inl"
