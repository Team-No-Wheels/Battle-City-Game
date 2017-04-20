
namespace AnonymousEngine
{
	namespace Core
	{
		template <typename MessageT>
		RTTI_DEFINITIONS(Event<MessageT>)

		template <typename MessageT>
		Vector<EventSubscriber*> Event<MessageT>::Subscribers = Vector<EventSubscriber*>();

		template <typename MessageT>
		std::mutex Event<MessageT>::SubscriberListMutex;

		template <typename MessageT>
		Event<MessageT>::Event(const MessageT& message) :
			EventPublisher(Subscribers, SubscriberListMutex), mMessage(message)
		{
		}

		template <typename MessageT>
		Event<MessageT>::Event(const Event& rhs) :
			EventPublisher(Subscribers, SubscriberListMutex), mMessage(rhs.mMessage)
		{
		}

		template <typename MessageT>
		Event<MessageT>::Event(Event&& rhs) noexcept :
			EventPublisher(Subscribers, SubscriberListMutex), mMessage(rhs.mMessage)
		{
			rhs.mMessage = nullptr;
		}

		template <typename MessageT>
		Event<MessageT>& Event<MessageT>::operator=(const Event& rhs)
		{
			mMessage = rhs.mMessage;
			return (*this);
		}

		template <typename MessageT>
		Event<MessageT>& Event<MessageT>::operator=(Event&& rhs) noexcept
		{
			mMessage = rhs.mMessage;
			rhs.mMessage = nullptr;
			return (*this);
		}

		template <typename MessageT>
		void Event<MessageT>::Subscribe(EventSubscriber& subscriber)
		{
			std::lock_guard<std::mutex> lock(SubscriberListMutex);
			Subscribers.PushBack(&subscriber);
		}

		template <typename MessageT>
		void Event<MessageT>::Unsubscribe(EventSubscriber& subscriber)
		{
			std::lock_guard<std::mutex> lock(SubscriberListMutex);
			Subscribers.Remove(&subscriber);
		}

		template <typename MessageT>
		void Event<MessageT>::UnsubscribeAll()
		{
			std::lock_guard<std::mutex> lock(SubscriberListMutex);
			Subscribers.Clear();
		}

		template <typename MessageT>
		const MessageT& Event<MessageT>::Message()
		{
			return mMessage;
		}
	}
}
