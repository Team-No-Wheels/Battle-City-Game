#pragma once

#include "RTTI.h"

namespace AnonymousEngine
{
	namespace Core
	{
		class EventPublisher : public RTTI
		{
		public:
			EventPublisher();
			virtual ~EventPublisher() = default;

			EventPublisher(const EventPublisher& rhs);
			EventPublisher(EventPublisher&& rhs) noexcept;

			EventPublisher& operator=(const EventPublisher& rhs);
			EventPublisher& operator=(EventPublisher&& rhs) noexcept;

			bool IsExpired() const;
			void Deliver();
			bool DeleteAfterPublishing() const;

		private:
			bool mIsExpired;
			bool mDeleteAfterPublishing;

			RTTI_DECLARATIONS(EventPublisher, RTTI);
		};
	}
}
