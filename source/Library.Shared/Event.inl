
namespace AnonymousEngine
{
	namespace Core
	{
		template <typename T>
		RTTI_DEFINITIONS(Event<T>);

		template <typename T>
		Vector<EventSubscriber*> Event<T>::Subscribers = Vector<EventSubscriber*>();

		template <typename T>
		Event<T>::Event(const T& message) :
			EventPublisher(&Subscribers), mMessage(&message)
		{
		}

		template <typename T>
		Event<T>::Event(Event& rhs) :
			EventPublisher(&Subscribers), mMessage(rhs.mMessage)
		{
		}

		template <typename T>
		Event<T>::Event(Event&& rhs) noexcept :
			EventPublisher(&Subscribers), mMessage(rhs.mMessage)
		{
			rhs.mMessage = nullptr;
		}

		template <typename T>
		Event<T>& Event<T>::operator=(Event& rhs)
		{
			mMessage = rhs.mMessage;
			return (*this);
		}

		template <typename T>
		Event<T>& Event<T>::operator=(Event&& rhs) noexcept
		{
			mMessage = rhs.mMessage;
			rhs.mMessage = nullptr;
			return (*this);
		}

		template <typename T>
		void Event<T>::Subscribe(EventSubscriber& subscriber)
		{
			Subscribers.PushBack(&subscriber);
		}

		template <typename T>
		void Event<T>::Unsubscribe(EventSubscriber& subscriber)
		{
			Subscribers.Remove(&subscriber);
		}

		template <typename T>
		void Event<T>::UnsubscribeAll()
		{
			Subscribers.Clear();
		}

		template <typename T>
		const T& Event<T>::Message()
		{
			return *mMessage;
		}
	}
}
