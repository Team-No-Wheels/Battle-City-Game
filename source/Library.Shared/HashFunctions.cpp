
#include "HashFunctions.h"
#include <cstdint>

namespace AnonymousEngine
{
	using namespace std;

	uint32_t SuperFastHash(const int8_t* data, uint32_t len)
	{
		uint32_t hash = len, tmp;
		int32_t rem;

		if (len <= 0 || data == nullptr)
		{
			return 0;
		}

		rem = len & 3;
		len >>= 2;

		/* Main loop */
		for (; len > 0; --len)
		{
			hash += (*reinterpret_cast<const uint16_t *>(data));
			tmp = ((*reinterpret_cast<const uint16_t *>(data + 2)) << 11) ^ hash;
			hash = (hash << 16) ^ tmp;
			data += 2 * sizeof(uint16_t);
			hash += hash >> 11;
		}

		/* Handle end cases */
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
		}

		/* Force "avalanching" of final 127 bits */
		hash ^= hash << 3;
		hash += hash >> 5;
		hash ^= hash << 4;
		hash += hash >> 17;
		hash ^= hash << 25;
		hash += hash >> 6;

		return hash;
	}
}