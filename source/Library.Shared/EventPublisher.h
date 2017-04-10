#pragma once

#include "RTTI.h"
#include "Vector.h"

namespace AnonymousEngine
{
	namespace Core
	{
		/** Base class for all event publishers
		 */
		class EventPublisher : public RTTI
		{
		public:
			/** Initialize the publisher instance
			 *  @param subscriberList The list of subscribers. This will be the address of a static list inside custom event class
			 */
			EventPublisher(Vector<class EventSubscriber*>* subscriberList);
			/** Release any allocated resources
			 */
			virtual ~EventPublisher() = default;

			/** Default copy constructor
			 */
			EventPublisher(const EventPublisher& rhs) = default;
			/** Default move constructor
			 */
			EventPublisher(EventPublisher&& rhs) noexcept = default;

			/** Default copy assignment operator
			 */
			EventPublisher& operator=(const EventPublisher& rhs) = default;
			/** Default move assignment operator
			 */
			EventPublisher& operator=(EventPublisher&& rhs) noexcept = default;

			/** Deliver the event with the message payload to all subscribers of this event type
			 */
			void Deliver();
		private:
			// This list is initialized during the constructor
			Vector<class EventSubscriber*>* mSubscribers;

			RTTI_DECLARATIONS(EventPublisher, RTTI);
		};
	}
}
