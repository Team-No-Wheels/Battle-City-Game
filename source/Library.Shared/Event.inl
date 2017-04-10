
namespace AnonymousEngine
{
	namespace Core
	{
		template <typename T>
		Event<T>::Event(Event& rhs)
		{}

		template <typename T>
		Event<T>::Event(Event&& rhs) noexcept
		{}

		template <typename T>
		Event<T>& Event<T>::operator=(Event& rhs)
		{
			return (*this);
		}

		template <typename T>
		Event<T>& Event<T>::operator=(Event&& rhs) noexcept
		{
			return (*this);
		}

		template <typename T>
		void Event<T>::Subscribe(EventSubscriber& subscriber)
		{}

		template <typename T>
		void Event<T>::Unsubscribe(EventSubscriber& subscriber)
		{}

		template <typename T>
		void Event<T>::UnsubscribeAll()
		{}

		template <typename T>
		const T& Event<T>::Message()
		{
			return mMessage;
		}

		template <typename T>
		RTTI_DEFINITIONS(Event<T>, EventPublisher);
	}
}
