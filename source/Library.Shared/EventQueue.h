#pragma once

#include "EventPublisher.h"
#include <memory>
#include "GameTime.h"
#include "Vector.h"

namespace AnonymousEngine
{
	namespace Core
	{
		class EventQueue final
		{
		public:
			void Enqueue(const std::shared_ptr<EventPublisher>& publisher, const GameTime& gameTime, std::uint32_t delay);
			void Update(const GameTime& gameTime);
			void Clear();
			bool IsEmpty() const;
			std::uint32_t Size() const;

			static void Send(const std::shared_ptr<EventPublisher>& publisher);
		private:
			struct QueueEntry
			{
				std::shared_ptr<EventPublisher> mPublisher;
				std::chrono::high_resolution_clock::time_point mEnqueuedTime;
				std::chrono::milliseconds mDelay;
			};

			uint32_t Partition(const GameTime& gameTime);

			Vector<QueueEntry> mEventQueue;
		};
	}
}
