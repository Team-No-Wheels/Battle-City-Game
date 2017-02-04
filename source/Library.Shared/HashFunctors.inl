
namespace AnonymousEngine
{
	template <typename T>
	std::uint32_t DefaultHashFunctor<T>::operator()(const T& data) const
	{
		return HashFunctions::SuperFastHash(reinterpret_cast<const std::int8_t*>(&data), sizeof(T));
	}
}
