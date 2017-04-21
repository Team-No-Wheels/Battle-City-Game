#pragma once

#include <future>
#include "EventSubscriber.h"
#include "HashMap.h"

namespace AnonymousEngine
{
	namespace Core
	{
		class EventQueue;
	}
}

namespace UnitTestLibraryDesktop
{
	class MultiThreadedSubscriber final : public AnonymousEngine::Core::EventSubscriber
	{
	public:
		enum class TestType
		{
			None,
			Enqueue,
			Clear,
			Subscribe,
			Unsubscribe,
			UnsubscribeAll,
			Exception
		};

		MultiThreadedSubscriber(AnonymousEngine::Core::EventQueue& eventQueue, TestType testType = TestType::None);
		~MultiThreadedSubscriber() = default;

		void Notify(AnonymousEngine::Core::EventPublisher& publisher) override;
		std::uint32_t NotifiedCount() const;

		typedef AnonymousEngine::HashMap<TestType, std::function<void(MultiThreadedSubscriber&)>> HandlerType;
	private:
		AnonymousEngine::Core::EventQueue& mEventQueue;
		TestType mTestType;
		std::uint32_t mNotifiedCount;
		std::mutex mMutex;

		static AnonymousEngine::HashMap<TestType, std::function<void(MultiThreadedSubscriber&)>> TestHandlers;

		static void EnqueueHandler(MultiThreadedSubscriber&);
		static void ClearHandler(MultiThreadedSubscriber&);
		static void SubscribeHandler(MultiThreadedSubscriber&);
		static void UnsubscribeHandler(MultiThreadedSubscriber&);
		static void UnsubscribeAllHandler(MultiThreadedSubscriber&);
		static void ExceptionHandler(MultiThreadedSubscriber&);

		static MultiThreadedSubscriber* Subscriber;
	};
}
