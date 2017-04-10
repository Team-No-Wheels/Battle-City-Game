#pragma once

#include "RTTI.h"
#include "Vector.h"

namespace AnonymousEngine
{
	namespace Core
	{
		class EventPublisher : public RTTI
		{
		public:
			EventPublisher(Vector<class EventSubscriber*>* subscriberList);
			virtual ~EventPublisher() = default;

			EventPublisher(const EventPublisher& rhs) = default;
			EventPublisher(EventPublisher&& rhs) noexcept = default;

			EventPublisher& operator=(const EventPublisher& rhs) = default;
			EventPublisher& operator=(EventPublisher&& rhs) noexcept = default;

			void Deliver();
		protected:
			Vector<class EventSubscriber*>* mSubscribers;

			RTTI_DECLARATIONS(EventPublisher, RTTI);
		};
	}
}
