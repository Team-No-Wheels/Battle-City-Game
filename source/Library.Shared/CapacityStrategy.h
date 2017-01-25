#pragma once

#include <cstdint>

namespace AnonymousEngine
{
	class CapacityStrategy
	{
		virtual std::uint32_t operator()(std::uint32_t size, std::uint32_t capacity) = 0;
	};

	class DefaultVectorCapacityStrategy : public CapacityStrategy
	{
		inline std::uint32_t operator()(std::uint32_t size, std::uint32_t capacity) override
		{
			if (capacity == 0)
			{
				return 3;
			}
			else
			{
				return size;
			}
		}
	};
}
