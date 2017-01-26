#pragma once

#include <cstdint>

namespace AnonymousEngine
{
	class CapacityStrategy
	{
	public:
		virtual std::uint32_t operator()(std::uint32_t size, std::uint32_t capacity) const = 0;
	};

	class DefaultVectorCapacityStrategy : public CapacityStrategy
	{
	public:
		inline std::uint32_t operator()(std::uint32_t size, std::uint32_t capacity) const override
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
