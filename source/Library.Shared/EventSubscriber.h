#pragma once

namespace AnonymousEngine
{
	namespace Core
	{
		/** Interface for an event subscriber
		 */
		class EventSubscriber
		{
		public:
			/** Initialize the interface
			 */
			EventSubscriber() = default;
			/** Release any interface allocated resources
			 */
			virtual ~EventSubscriber() = default;
			/** Notify the subscriber about an event
			 *  @param publisher The publisher of the event. Event data is retrived from this publisher
			 */
			virtual void Notify(class EventPublisher& publisher) = 0;
		};
	}
}
