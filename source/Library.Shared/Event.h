#pragma once

#include "EventPublisher.h"
#include "RTTI.h"

namespace AnonymousEngine
{
	namespace Core
	{
		template <typename MessageT>
		class Event final : public EventPublisher
		{
		public:
			/** Initialize event with a message object
			 *  @param message The message to send with this event
			 */
			Event(const MessageT& message);
			/** Release any allocated resources and finalize
			 */
			~Event() = default;

			/** Initialize an event from the values of another event object
			 *  @param rhs The event to copy data from
			 */
			Event(const Event& rhs);
			/** Initialize an event from the values of another event object
			 *  @param rhs The event to move data from
			 */
			Event(Event&& rhs) noexcept;

			/** Copy value values of another event object to this
			 *  @param rhs The event to copy data from
			 */
			Event& operator=(const Event& rhs);
			/** Move value values of another event object to this
			 *  @param rhs The event to move data from
			 */
			Event& operator=(Event&& rhs) noexcept;

			/** Subscribe to this event
			 *  @param subscriber The subscriber who wants to subscribe to this event
			 */
			static void Subscribe(class EventSubscriber& subscriber);
			/** Unsubscribe from this event
			 *  @param subscriber The subscriber who wants to unsubscribe from this event
			 */
			static void Unsubscribe(class EventSubscriber& subscriber);
			/** Unsubscribe all subscribers from this event
			 */
			static void UnsubscribeAll();

			/** Get the message payload
			 */
			const MessageT& Message();

		private:
			// Message payload
			const MessageT& mMessage;

			// List of all subscribers to this event type
			static Vector<EventSubscriber*> Subscribers;

			RTTI_DECLARATIONS(Event, EventPublisher)
		};
	}
}

#include "Event.inl"
