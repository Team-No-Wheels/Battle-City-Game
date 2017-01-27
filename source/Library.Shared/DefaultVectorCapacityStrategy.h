#pragma once

#include "CapacityStrategy.h"

namespace AnonymousEngine
{
	/** Default capacity strategy used by the Vector container
	*/
	class DefaultVectorCapacityStrategy : public CapacityStrategy
	{
	public:
		/** Construct default capacity strategy with default initialization
		*/
		DefaultVectorCapacityStrategy() = default;
		/** Clear any allocated resources
		*/
		~DefaultVectorCapacityStrategy() = default;

		/** Provide a capacity increment value given the current size and current capacity of the vector
		*  @param size The current size of the vector
		*  @param capacity The current capacity of the vector
		*  @return The increment by which capacity should be incremented. This implementation returns a constant value 3
		*/
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
