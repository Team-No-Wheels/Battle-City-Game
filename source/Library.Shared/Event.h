#pragma once

#include "EventPublisher.h"
#include "RTTI.h"

namespace AnonymousEngine
{
	namespace Core
	{
		template <typename T>
		class Event final : public EventPublisher
		{
		public:
			Event(const T& message);
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
			const T* mMessage;

			static Vector<EventSubscriber*> Subscribers;

			RTTI_DECLARATIONS(Event, EventPublisher);
		};
	}
}

#include "Event.inl"
