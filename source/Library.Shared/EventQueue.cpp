#include "EventQueue.h"

namespace AnonymousEngine
{
	namespace Core
	{
		using namespace std::chrono;

		#pragma region QueueEntryMethods

		bool EventQueue::QueueEntry::operator==(const QueueEntry& rhs) const
		{
			return (mDelay == rhs.mDelay) && (mEnqueuedTime == rhs.mEnqueuedTime) && (mPublisher == rhs.mPublisher);
		}

		bool EventQueue::QueueEntry::operator!=(const QueueEntry& rhs) const
		{
			return !((*this) == rhs);
		}

		#pragma endregion 

		#pragma region EventQueueMethods

		void EventQueue::Enqueue(const std::shared_ptr<EventPublisher>& publisher, const GameTime& gameTime, std::uint32_t delay)
		{
			mEventQueue.PushBack({publisher, gameTime, std::chrono::milliseconds(delay)});
		}

		void EventQueue::Update(const GameTime& gameTime)
		{
			if (mEventQueue.Size() > 1)
			{
				std::uint32_t upperNonExpiredIndex = mEventQueue.Size() - 1;
				for (std::uint32_t index = 0; index < upperNonExpiredIndex - 1; ++index)
				{
					auto& entry = mEventQueue[index];
					if ((entry.mEnqueuedTime.CurrentTime() + entry.mDelay) <= gameTime.CurrentTime())
					{
						entry.mPublisher->Deliver();
						entry.mPublisher.reset();
						mEventQueue[index] = std::move(mEventQueue[upperNonExpiredIndex]);
						--index;
						--upperNonExpiredIndex;
					}
				}
			}
		}

		void EventQueue::Clear()
		{
			mEventQueue.Clear();
		}

		bool EventQueue::IsEmpty() const
		{
			return mEventQueue.IsEmpty();
		}

		std::uint32_t EventQueue::Size() const
		{
			return mEventQueue.Size();
		}

		void EventQueue::Send(const std::shared_ptr<EventPublisher>& publisher)
		{
			publisher->Deliver();
		}

		#pragma endregion
	}
}
