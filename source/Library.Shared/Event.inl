
namespace AnonymousEngine
{
	namespace Core
	{
		template <typename MessageT>
		RTTI_DEFINITIONS(Event<MessageT>)

		template <typename MessageT>
		Vector<EventSubscriber*> Event<MessageT>::Subscribers = Vector<EventSubscriber*>();

		template <typename MessageT>
		Event<MessageT>::Event(const MessageT& message) :
			EventPublisher(Subscribers), mMessage(message)
		{
		}

		template <typename MessageT>
		Event<MessageT>::Event(const Event& rhs) :
			EventPublisher(Subscribers), mMessage(rhs.mMessage)
		{
		}

		template <typename MessageT>
		Event<MessageT>::Event(Event&& rhs) noexcept :
			EventPublisher(Subscribers), mMessage(rhs.mMessage)
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
			Subscribers.PushBack(&subscriber);
		}

		template <typename MessageT>
		void Event<MessageT>::Unsubscribe(EventSubscriber& subscriber)
		{
			Subscribers.Remove(&subscriber);
		}

		template <typename MessageT>
		void Event<MessageT>::UnsubscribeAll()
		{
			Subscribers.Clear();
		}

		template <typename MessageT>
		const MessageT& Event<MessageT>::Message()
		{
			return mMessage;
		}
	}
}
