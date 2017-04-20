#include "EventQueue.h"

namespace AnonymousEngine
{
	namespace Core
	{
		using namespace std::chrono;

#pragma region EventQueueMethods

		void EventQueue::Enqueue(const std::shared_ptr<EventPublisher>& publisher, const GameTime& gameTime, std::uint32_t delay)
		{
			mEventQueue.PushBack({
				publisher, gameTime.CurrentTime(),
				std::chrono::milliseconds(delay)
			});
		}

		void EventQueue::Update(const GameTime& gameTime)
		{
			Vector<QueueEntry> mTempEventQueue;

			// lock the event queue and move expired events to temp queue
			{
				std::lock_guard<std::mutex> lock(mMutex);
				std::uint32_t expiredStart = Partition(gameTime);
				for (std::uint32_t index = expiredStart; index < mEventQueue.Size(); ++index)
				{
					mTempEventQueue.PushBack(mEventQueue[index]);
				}
				mEventQueue.Remove(mEventQueue.IteratorAt(expiredStart), mEventQueue.end());
			}

			Vector<std::future<void>> futures;
			for (auto& entry : mTempEventQueue)
			{
				futures.PushBack(std::async([&entry]()
				{
					entry.mPublisher->Deliver();
				}));
			}
			for (auto& f : futures)
			{
				f.get();
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

		std::uint32_t EventQueue::Partition(const GameTime& gameTime)
		{
			std::uint32_t upperNonExpiredIndex = mEventQueue.Size();
			for (std::uint32_t index = 0; index < upperNonExpiredIndex; ++index)
			{
				auto& entry = mEventQueue[index];
				if ((entry.mEnqueuedTime + entry.mDelay) <= gameTime.CurrentTime())
				{
					--upperNonExpiredIndex;
					if (index != upperNonExpiredIndex)
					{
						std::swap(mEventQueue[index], mEventQueue[upperNonExpiredIndex]);
					}
					--index;
				}
			}
			return upperNonExpiredIndex;
		}

#pragma endregion
	}
}
