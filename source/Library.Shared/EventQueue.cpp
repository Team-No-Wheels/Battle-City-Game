#include "EventQueue.h"
#include <algorithm>

namespace AnonymousEngine
{
	namespace Core
	{
		using namespace std::chrono;

		void EventQueue::Enqueue(std::shared_ptr<EventPublisher> publisher, const GameTime& gameTime, std::uint32_t delay)
		{
			mEventQueue.PushBack({publisher, gameTime, std::chrono::milliseconds(delay)});
		}

		bool EventQueue::Send(std::shared_ptr<EventPublisher> publisher)
		{
			publisher->Deliver();
			QueueEntry* entryToSend = nullptr;
			for (auto& entry : mEventQueue)
			{
				if (&entry.mPublisher == &publisher)
				{
					entryToSend = &entry;
					break;
				}
			}

			if (entryToSend != nullptr)
			{
				entryToSend->mPublisher->Deliver();
				mEventQueue.Remove(*entryToSend);
				return true;
			}
			return false;
		}

		void EventQueue::Update(const GameTime& gameTime)
		{
			if (mEventQueue.Size() > 1)
			{
				std::uint32_t upperNonExpiredIndex = mEventQueue.Size() - 1;
				for (std::uint32_t index = 0; index < upperNonExpiredIndex - 1; ++index)
				{
					auto& entry = mEventQueue[index];
					if ((entry.mEnqueuedTime.CurrentTime() + entry.mDelay) > gameTime.CurrentTime())
					{
						//mEventQueue[index] = std::move(mEventQueue[upperNonExpiredIndex]);
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
	}
}
