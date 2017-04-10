#pragma once

#include "EventPublisher.h"
#include <memory>
#include "GameTime.h"
#include "Vector.h"

namespace AnonymousEngine
{
	namespace Core
	{
		class EventQueue
		{
		public:
			void Enqueue(std::shared_ptr<EventPublisher> publisher, const GameTime& gameTime, std::uint32_t delay);
			bool Send(std::shared_ptr<EventPublisher> publisher);
			void Update(const GameTime& gameTime);
			void Clear();
			bool IsEmpty() const;
			std::uint32_t Size() const;

		private:
			struct QueueEntry
			{
				std::shared_ptr<EventPublisher> mPublisher;
				GameTime mEnqueuedTime;
				std::chrono::milliseconds mDelay;
			};

			Vector<QueueEntry> mEventQueue;
		};
	}
}
