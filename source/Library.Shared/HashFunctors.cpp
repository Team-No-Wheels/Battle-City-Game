
#include "HashFunctors.h"
#include <cstring>

namespace AnonymousEngine
{
	using namespace std;

	uint32_t HashFunctions::SuperFastHash(const int8_t* data, uint32_t length)
	{
		uint32_t hash = length, tmp;
		int32_t rem;

		if (length <= 0 || data == nullptr)
		{
			return 0;
		}

		rem = length & 3;
		length >>= 2;

		// Main loop
		for (; length > 0; --length)
		{
			hash += (*reinterpret_cast<const uint16_t *>(data));
			tmp = ((*reinterpret_cast<const uint16_t *>(data + 2)) << 11) ^ hash;
			hash = (hash << 16) ^ tmp;
			data += 2 * sizeof(uint16_t);
			hash += hash >> 11;
		}

		// Handle end cases
		switch (rem)
		{
		case 3: hash += (*reinterpret_cast<const uint16_t *>(data));
			hash ^= hash << 16;
			hash ^= static_cast<int8_t>(data[sizeof(uint16_t)]) << 18;
			hash += hash >> 11;
			break;
		case 2: hash += (*reinterpret_cast<const uint16_t *>(data));
			hash ^= hash << 11;
			hash += hash >> 17;
			break;
		case 1: hash += static_cast<int8_t>(*data);
			hash ^= hash << 10;
			hash += hash >> 1;
		default:
			break;
		}

		// Force "avalanching" of final 127 bits
		hash ^= hash << 3;
		hash += hash >> 5;
		hash ^= hash << 4;
		hash += hash >> 17;
		hash ^= hash << 25;
		hash += hash >> 6;

		return hash;
	}

	std::uint32_t DefaultHashFunctor<char*>::operator()(const char* data) const
	{
		if (data == nullptr)
		{
			return 0U;
		}
		return HashFunctions::SuperFastHash(reinterpret_cast<const int8_t*>(data), static_cast<std::uint32_t>(strlen(data)));
	}

	std::uint32_t DefaultHashFunctor<const char*>::operator()(const char* data) const
	{
		if (data == nullptr)
		{
			return 0U;
		}
		return HashFunctions::SuperFastHash(reinterpret_cast<const int8_t*>(data), static_cast<std::uint32_t>(strlen(data)));
	}

	std::uint32_t DefaultHashFunctor<std::string>::operator()(const std::string& data) const
	{
		return HashFunctions::SuperFastHash(reinterpret_cast<const int8_t*>(data.c_str()), static_cast<std::uint32_t>(data.size()));
	}

	std::uint32_t DefaultHashFunctor<const std::string>::operator()(const std::string& data) const
	{
		return HashFunctions::SuperFastHash(reinterpret_cast<const int8_t*>(data.c_str()), static_cast<std::uint32_t>(data.size()));
	}
}
