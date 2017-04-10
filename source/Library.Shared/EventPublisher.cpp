#include "EventPublisher.h"

namespace AnonymousEngine
{
	namespace Core
	{
		EventPublisher::EventPublisher() :
			mIsExpired(false), mDeleteAfterPublishing(false)
		{
		}

		EventPublisher::EventPublisher(const EventPublisher& rhs) :
			mIsExpired(rhs.mIsExpired), mDeleteAfterPublishing(rhs.DeleteAfterPublishing())
		{
		}

		EventPublisher::EventPublisher(EventPublisher&& rhs) noexcept:
			mIsExpired(rhs.mIsExpired), mDeleteAfterPublishing(rhs.DeleteAfterPublishing())
		{
		}

		EventPublisher& EventPublisher::operator=(const EventPublisher& rhs)
		{
			mIsExpired = rhs.mIsExpired;
			mDeleteAfterPublishing = rhs.DeleteAfterPublishing();
			return (*this);
		}

		EventPublisher& EventPublisher::operator=(EventPublisher&& rhs) noexcept
		{
			mIsExpired = rhs.mIsExpired;
			mDeleteAfterPublishing = rhs.DeleteAfterPublishing();
			return (*this);
		}

		bool EventPublisher::IsExpired() const
		{
			return mIsExpired;
		}

		void EventPublisher::Deliver()
		{
		}

		bool EventPublisher::DeleteAfterPublishing() const
		{
			return mDeleteAfterPublishing;
		}
	}
}
