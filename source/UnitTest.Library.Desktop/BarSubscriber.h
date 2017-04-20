#pragma once

#include "EventSubscriber.h"
#include "Bar.h"
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
	class BarSubscriber final : public AnonymousEngine::Core::EventSubscriber
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
			Destroy
		};

		BarSubscriber(AnonymousEngine::Core::EventQueue& eventQueue, TestType testType = TestType::None);
		~BarSubscriber() = default;
		void Notify(AnonymousEngine::Core::EventPublisher& publisher) override;
		bool IsNotified() const;
		const Bar* EventData() const;
	private:
		AnonymousEngine::Core::EventQueue& mEventQueue;
		TestType mTestType;
		bool mIsNotified;
		Bar* mData;

		static AnonymousEngine::HashMap<TestType, std::function<void(Bar*)>> TestHandlers;
	};
}
