#pragma once

#include "EventPublisher.h"
#include <future>
#include <memory>
#include "GameTime.h"
#include "Vector.h"

namespace AnonymousEngine
{
	namespace Core
	{
		/** Maintains a queue of event which gets delivered based on time
		*/
		class EventQueue final
		{
		public:
			/** Add an event to the queue
			*  @param publisher The event publisher to be enqueued
			*  @param gameTime The time at which the event is being enqueued
			*  @param delay The number of milliseconds after which this event is to be delivered
			*/
			void Enqueue(const std::shared_ptr<EventPublisher>& publisher, const GameTime& gameTime, std::uint32_t delay);

			/** Process all the events in the queue and deliver the events which are expired
			*  @param gameTime The current time
			*/
			void Update(const GameTime& gameTime);

			/** Clear the event queue
			*/
			void Clear();

			/** Whether the event queue is empty or not
			*  @return A bool which indicates whether the queue is empty or not
			*/
			bool IsEmpty() const;
			/** The number of events queued
			*  @return The size of the event queue
			*/
			std::uint32_t Size() const;

			/** Deliver the given event publisher
			*  @param publisher The event to publish
			*/
			static void Send(const std::shared_ptr<EventPublisher>& publisher);
		private:
			// Represents an entry in the queue
			struct QueueEntry
			{
				std::shared_ptr<EventPublisher> mPublisher;
				std::chrono::high_resolution_clock::time_point mEnqueuedTime;
				std::chrono::milliseconds mDelay;
			};

			// Paritions the event queue based on expired vs non-expired
			std::uint32_t Partition(const GameTime& gameTime);

			// Mutex used to lock the queue
			std::mutex mMutex;

			// The event queue
			Vector<QueueEntry> mEventQueue;
		};
	}
}
