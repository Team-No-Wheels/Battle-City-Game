
#include "HashFunctors.h"
#include "HashFunctions.h"
#include <cstring>

namespace AnonymousEngine
{
	std::uint32_t DefaultHashFunctor<char*>::operator()(const char*& data) const
	{
		return SuperFastHash(reinterpret_cast<const int8_t*>(data), static_cast<std::uint32_t>(strlen(data)));
	}

	std::uint32_t DefaultHashFunctor<const char*>::operator()(const char*& data) const
	{
		return SuperFastHash(reinterpret_cast<const int8_t*>(data), static_cast<std::uint32_t>(strlen(data)));
	}

	std::uint32_t DefaultHashFunctor<std::string>::operator()(const std::string& data) const
	{
		return SuperFastHash(reinterpret_cast<const int8_t*>(data.c_str()), static_cast<std::uint32_t>(data.size()));
	}

	std::uint32_t DefaultHashFunctor<const std::string>::operator()(const std::string& data) const
	{
		return SuperFastHash(reinterpret_cast<const int8_t*>(data.c_str()), static_cast<std::uint32_t>(data.size()));
	}
}
