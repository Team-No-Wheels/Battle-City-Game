#pragma once

#include <future>
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
			/** Deliver the event with the message payload to all subscribers of this event type
			 */
			void Deliver();
		protected:
			/** Initialize the publisher instance
			 *  @param subscriberList The list of subscribers. This will be the address of a static list inside custom event class
			 */
			EventPublisher(const Vector<class EventSubscriber*>& subscriberList, std::mutex& mutex);
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
		private:
			// This list is initialized during the constructor
			const Vector<class EventSubscriber*>& mSubscribers;
			
			// Mutex to lock on the subscriber list
			std::mutex& mListMutex;

			RTTI_DECLARATIONS(EventPublisher, RTTI);
		};
	}
}
